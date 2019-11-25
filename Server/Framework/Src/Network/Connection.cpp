#include <Network/Connection.h>
#include <Network/Packet.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <fstream>

namespace Swtor
{
    namespace Network
    {
        //---------------------------------------------------------------------
        Connection::Connection(boost::asio::io_service& pIoService)
            : mSocket(pIoService)
        {
        }
        //---------------------------------------------------------------------
        Connection::~Connection()
        {
        }
        //---------------------------------------------------------------------
        void Connection::Close()
        {
            if (mSocket.is_open())
            {
                try
                {
                    mSocket.shutdown(boost::asio::socket_base::shutdown_both);
                }
                catch(...)
                {
                }

                try
                {
                    mSocket.close();
                }
                catch(...)
                {
                }
            }
        }
        //---------------------------------------------------------------------
        void Connection::Start()
        {
            async_read();
        }
        //---------------------------------------------------------------------
        void Connection::Write(Packet& pData)
        {
            mSocket.get_io_service().post(boost::bind(&Connection::DoWrite, shared_from_this(), pData));
        }
        //---------------------------------------------------------------------
        void Connection::DoWrite(Packet pData)
        {
            bool write_in_progress = !mToSend.empty();
            mToSend.push_back(pData);
            if (!write_in_progress)
            {
                mToSend.front().Finalize();
                async_write(mToSend.front());
            }
        }
        //---------------------------------------------------------------------
        void Connection::HandleRead(const boost::system::error_code& pError)
        {
            if (!pError)
            {
                mPacketLock.lock();
                mPackets.push_back(mReceivingPacket);
                mPacketLock.unlock();

                if (mCipher)
                    async_read();
            }
            else
                Close();
        }
        //---------------------------------------------------------------------
        void Connection::HandleWrite(const boost::system::error_code& pError)
        {
            if (!pError)
            {
                mToSend.pop_front();

                if (!mToSend.empty())
                    async_write(mToSend.front());
            }
            else
                Close();
        }
        //---------------------------------------------------------------------
        boost::asio::ip::tcp::socket& Connection::GetSocket()
        {
            return mSocket;
        }
        //---------------------------------------------------------------------
        void Connection::async_write(Packet& pPacket)
        {
            if(mCipher)
            {
                std::string data = pPacket.GetHeader().substr(6) + pPacket.GetBuffer();

                std::string compressedPayload = mCipher->Compress(data);
                pPacket.Size = (uint32_t)compressedPayload.size() + 6;

                mOutboundData = pPacket.GetHeader().substr(0,6) + compressedPayload;
                mOutboundData = mCipher->Encrypt(mOutboundData);
            }
            else
            {
                pPacket.Size = (uint32_t)pPacket.GetBuffer().size() + 14;
                mOutboundData = pPacket.GetHeader() + pPacket.GetBuffer();
            }

            boost::asio::async_write(mSocket, boost::asio::buffer(mOutboundData), boost::bind(&Connection::HandleWrite, shared_from_this(), boost::asio::placeholders::error));
        }
        //---------------------------------------------------------------------
        void Connection::async_read()
        {
            // Read the header
            boost::asio::async_read(mSocket, boost::asio::buffer(mInboundHeader), boost::asio::transfer_exactly(6),
                boost::bind(&Connection::handle_read_header,shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }
        //---------------------------------------------------------------------
        void Connection::handle_read_header(const boost::system::error_code& e, size_t transfered)
        {
            if (e)
                this->HandleRead(e);
            else
            {
                std::string data(mInboundHeader, 6);

                // If encryption is enabled, decrypt the header
                if (mCipher)
                    data = mCipher->Decrypt(data);
                // Initialize the header
                mReceivingPacket.InitializeHeader(data);

                if (mReceivingPacket.Size > 1<<16)
                {
                    boost::system::error_code error(boost::asio::error::invalid_argument);
                    this->HandleRead(error);
                    return;
                }

                // Ready up the buffer
                mInboundData.resize(mReceivingPacket.Size - 6);

                // Read the buffer
                boost::asio::async_read(mSocket, boost::asio::buffer(mInboundData), boost::asio::transfer_exactly(mInboundData.size()),
                    boost::bind(&Connection::handle_read_data, shared_from_this(),
                    boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            }
        }
        //---------------------------------------------------------------------
        void Connection::handle_read_data(const boost::system::error_code& e, size_t pBytes)
        {
            // If error tell the caller.
            if (e)
                this->HandleRead(e);
            else
            {
                // Try to handle the payload
                try
                {
                    // If encryption is enabled
                    if (mCipher)
                    {
                        std::string data(&mInboundData[0], mInboundData.size());
                        // Decrypt then decompress the payload
                        data = mCipher->Decompress(mCipher->Decrypt(data));

                        if (!data.empty())
                        {
                            //System::PrintBinary((unsigned char*)&data[0], data.size(), "Client -> Server");
                            // Initialize the packet buffer
                            mReceivingPacket.Initialize(data);
                            // Extract the header
                            mReceivingPacket >> mReceivingPacket.Opcode;
                            mReceivingPacket >> mReceivingPacket.ContentV;
                            mReceivingPacket >> mReceivingPacket.TransportV;
                        }
                    }
                    else // Initialize the packet buffer
                        mReceivingPacket.Initialize(mInboundData);
                }
                catch (...)
                {
                    // Unable to decode data.
                    boost::system::error_code error(boost::asio::error::invalid_argument);
                    this->HandleRead(error);
                    return;
                }

                // Inform caller that data has been received ok.
                this->HandleRead(e);
            }
        }
        //---------------------------------------------------------------------
        Packet Connection::PopPacket()
        {
            mPacketLock.lock();
            Packet packet = mPackets.front();
            mPackets.pop_front();
            mPacketLock.unlock();

            return packet;
        }
        //---------------------------------------------------------------------
        bool Connection::HasPacket()
        {
            return !mPackets.empty();
        }
        //---------------------------------------------------------------------
        void Connection::SetCipher(Crypt::Cipher* pCipher)
        {
            mCipher.reset(pCipher);
        }
        //---------------------------------------------------------------------
        bool Connection::IsOffline()
        {
            return !mSocket.is_open();
        }
        //---------------------------------------------------------------------
    }
}