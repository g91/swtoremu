#pragma once

#include <Network/Connection.h>
#include <Network/IoServicePool.h>
#include <System/EventListener.h>
#include <System/DBWorkQueue.h>
#include <System/WorkQueue.h>
#include <boost/signal.hpp>

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
		class DECLDIR Server
			: public System::EventListener, private boost::noncopyable
		{
		public:

			/**
			 * Instantiate the server
			 * @param pPort The port to start the server on
			 */
			Server(uint16_t pPort);
			/**
			 * Start the server, will return on exit
			 */
			void Start();
			/**
			 * Authentication and sync loop
			 */
			void Run();
			/**
			 * Stops the server, Run will return
			 */
			void Stop();

			virtual void OnEvent(std::shared_ptr<System::Event> pEvent);

			boost::signal<void(Connection::pointer)>	OnConnection;
			boost::signal<void(uint32_t)>				OnUpdate;

		protected:

			void Accept();
			void HandleAccept(Connection::pointer pSession, const boost::system::error_code& pError);

			/**
			 * Scale the thread count according to the runtime infos.
			 */
			void Scale();

		private:

			std::unique_ptr<boost::asio::ip::tcp::acceptor>			mAcceptor;
			std::unique_ptr<IoServicePool>							mIoPool;
			uint16_t												mPort;

			boost::mutex							mGuard;
			boost::timer							mTimer;

			bool mStarted;
		};
	}
}