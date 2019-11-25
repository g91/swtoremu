#pragma once

#include <System/EventListener.h>
#include <Network/Packet.h>
#include <Crypt/Cipher.h>

#include <boost/asio.hpp>
#include <boost/signal.hpp>
#include <boost/tuple/tuple.hpp>

#include <deque>
#include <unordered_map>

#if defined(WIN32)
#if defined FRAMEWORK_EXPORTS
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
#else
#define DECLDIR
#endif

namespace Swtor
{
	namespace Network
	{
		// Forward declaration
		typedef std::deque<Packet> PacketQueue;

		/**
		 * @class Connection
		 * @brief Handles a single client as a session
		 */
		class DECLDIR Connection : private boost::noncopyable, public boost::enable_shared_from_this<Connection>
		{
		public:

			typedef boost::shared_ptr<Connection> pointer;

			Connection(boost::asio::io_service& pIoService);
			virtual ~Connection();

			/**
			 * Starts listening to the session
			 */
			void Start();

			/**
			 * Write a packet to the session, non blocking, undefined timing
			 * @param pData The packet to send
			 */
			void Write(Packet& pData);

			/**
			 * Close the connection, will trigger scalar destruction
			 */
			void Close();

			/**
			 * Get the session's socket
			 * @return The socket
			 */
			boost::asio::ip::tcp::socket& GetSocket();

			/**
			 * Get the oldest packet and remove it from the packet queue
			 * @return A packet
			 */
			Packet PopPacket();

			/**
			 * True if queue > 0, false otherwise
			 * @return
			 */
			bool HasPacket();

			/**
			 * Sets the cipher
			 * @param pCipher The cipher to use
			 */
			void SetCipher(Crypt::Cipher* pCipher);


			/**
			 * Too complicated to be explained xD
			 */
			bool IsOffline();

		protected:

			void async_write(Packet& pPacket);
			void async_read();
			void handle_read_header(const boost::system::error_code& e, size_t transfered);
			void handle_read_data(const boost::system::error_code& e, size_t pBytes);

			void HandleRead	(const boost::system::error_code& pError);
			void HandleWrite(const boost::system::error_code& pError);
			void DoWrite(Packet data);

		private:

			enum { header_length = 6 };
			std::string mOutboundData; //< Outbound data buffer, kept for reference
			char mInboundHeader[header_length]; //< Header buffer
			std::vector<char>  mInboundData; //< Buffer

			Packet mReceivingPacket;
			boost::mutex mPacketLock;

			PacketQueue mPackets;
			PacketQueue mToSend;
			
			std::unique_ptr<Crypt::Cipher>  mCipher;
			boost::asio::ip::tcp::socket	mSocket;
		};
	}
}