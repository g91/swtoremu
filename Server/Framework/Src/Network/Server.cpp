#include <Crypt/RSA.h>
#include <Network/Server.h>
#include <System/Log.h>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace Swtor
{
	namespace Network
	{
		//---------------------------------------------------------------------
		Server::Server(unsigned short pPort)
			:mPort(pPort),mStarted(false)
		{
		}
		//---------------------------------------------------------------------
		void Server::Scale()
		{
			unsigned int logicThreads = boost::thread::hardware_concurrency();

			mIoPool.reset(new IoServicePool(2));
			mAcceptor.reset(new boost::asio::ip::tcp::acceptor(mIoPool->GetIoService(), tcp::endpoint(tcp::v4(), mPort)));

			System::Log::Print("Running with : - 2 Network thread(s) ");
			System::Log::Print("CPU : " + std::to_string((unsigned long long)logicThreads) + " Logic thread(s)");
			System::Log::Print("");
		}
		//---------------------------------------------------------------------
		void Server::Start()
		{
			// note : Order matters !
			Scale();
			Accept();

			System::Log::Print("Waiting for connections.");
			mStarted = true;

			Run();
		}
		//---------------------------------------------------------------------
		void Server::Run()
		{
			mIoPool->Run();

			uint32_t totalElasped = 0;

			while(mStarted)
			{
				totalElasped += uint32_t(mTimer.elapsed() * 1000);
				mTimer.restart();

				OnUpdate(totalElasped);

				System::Log::Flush();

				totalElasped = uint32_t(mTimer.elapsed() * 1000);
				mTimer.restart();

				if(totalElasped < 50)
				{
					// This thread doesn't need to be very responsive
					boost::this_thread::sleep(boost::posix_time::milliseconds(50 - totalElasped));
				}
			}
		}
		//---------------------------------------------------------------------
		void Server::Stop()
		{
			mStarted = false;
		}
		//---------------------------------------------------------------------
		void Server::Accept()
		{
			Connection::pointer session = boost::make_shared<Connection>(mIoPool->GetIoService());
			mAcceptor->async_accept(session->GetSocket(),
				boost::bind(&Server::HandleAccept, this,
				session, boost::asio::placeholders::error));
		}
		//---------------------------------------------------------------------
		void Server::HandleAccept(Connection::pointer pSession, const boost::system::error_code& pError)
		{
			if(!pError)
			{
				OnConnection(pSession);
				pSession->Start();
			}
			else
			{
				System::Log::Error(pError.message());
			}
			Accept();
		}
		//---------------------------------------------------------------------
		void Server::OnEvent(std::shared_ptr<System::Event> pEvent)
		{
			if(!mStarted)
			{
				mGuard.unlock();
			}
		}
		//---------------------------------------------------------------------
	}
}