#include <Network/TimeConnection.h>
#include <Network/Packet.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <fstream>

namespace Swtor
{
	namespace Network
	{
		//---------------------------------------------------------------------
		TimeConnection::TimeConnection(boost::asio::io_service& pIoService)
			: mSocket(pIoService)
		{
		}
		//---------------------------------------------------------------------
		TimeConnection::~TimeConnection()
		{
		}
		//---------------------------------------------------------------------
		void TimeConnection::Close()
		{
			if(mSocket.is_open())
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
		void TimeConnection::Start()
		{
			async_read();
		}
		//---------------------------------------------------------------------
		void TimeConnection::Write(Packet& pData)
		{
			mSocket.get_io_service().post(boost::bind(&TimeConnection::DoWrite, shared_from_this(), pData));
		}
		//---------------------------------------------------------------------
		void TimeConnection::DoWrite(Packet pData)
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
		void TimeConnection::HandleRead(const boost::system::error_code& pError)
		{
			if(!pError)
			{
				mPacketLock.lock();
				mPackets.push_back(mReceivingPacket);
				mPacketLock.unlock();

				async_read();
			}
			else
			{
				Close();
			}
		}
		//---------------------------------------------------------------------
		void TimeConnection::HandleWrite(const boost::system::error_code& pError)
		{
			if(!pError)
			{
				mToSend.pop_front();
				if (!mToSend.empty())
				{
					async_write(mToSend.front());
				}
			}
			else
			{
				Close();
			}
		}
		//---------------------------------------------------------------------
		boost::asio::ip::tcp::socket& TimeConnection::GetSocket()
		{
			return mSocket;
		}
		//---------------------------------------------------------------------
		void TimeConnection::async_write(Packet& pPacket)
		{
			uint8_t size = pPacket.GetBuffer().size();
			mOutboundData.append((const char*)&size, 1);
			mOutboundData += pPacket.GetBuffer();

			boost::asio::async_write(mSocket, boost::asio::buffer(mOutboundData), boost::bind(&TimeConnection::HandleWrite, shared_from_this(), boost::asio::placeholders::error));
		}
		//---------------------------------------------------------------------
		void TimeConnection::async_read()
		{
			// Read the header
			boost::asio::async_read(mSocket, boost::asio::buffer(mInboundHeader), boost::asio::transfer_exactly(header_length),
				boost::bind(&TimeConnection::handle_read_header,shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
		//---------------------------------------------------------------------
		void TimeConnection::handle_read_header(const boost::system::error_code& e, size_t transfered)
		{
			if (e)
			{
				this->HandleRead(e);
			}
			else
			{
				// Ready up the buffer
				mInboundData.resize((size_t)mInboundHeader[0]);

				// Read the buffer
				boost::asio::async_read(mSocket, boost::asio::buffer(mInboundData), boost::asio::transfer_exactly(mInboundData.size()),
					boost::bind(&TimeConnection::handle_read_data, shared_from_this(),
					boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			}
		}
		//---------------------------------------------------------------------
		void TimeConnection::handle_read_data(const boost::system::error_code& e, size_t pBytes)
		{
			// If error tell the caller.
			if (e)
			{
				this->HandleRead(e);
			}
			else
			{
				// Try to handle the payload
				try
				{
					// Initialize the packet buffer
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
		Packet TimeConnection::PopPacket()
		{
			mPacketLock.lock();
			Packet packet = mPackets.front();
			mPackets.pop_front();
			mPacketLock.unlock();

			return packet;
		}
		//---------------------------------------------------------------------
		bool TimeConnection::HasPacket()
		{
			return !mPackets.empty();
		}
		//---------------------------------------------------------------------
		bool TimeConnection::IsOffline()
		{
			return !mSocket.is_open();
		}
		//---------------------------------------------------------------------
	}
}