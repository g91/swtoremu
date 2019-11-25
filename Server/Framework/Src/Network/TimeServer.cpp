#include <Crypt/RSA.h>
#include <Network/TimeServer.h>
#include <System/Log.h>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace Swtor
{
	namespace Network
	{
		//---------------------------------------------------------------------
		TimeServer::TimeServer(unsigned short pPort)
			:mPort(pPort),mStarted(false)
		{
		}
		//---------------------------------------------------------------------
		void TimeServer::Scale()
		{
			unsigned int logicThreads = boost::thread::hardware_concurrency();

			mIoPool.reset(new IoServicePool(2));
			mAcceptor.reset(new boost::asio::ip::tcp::acceptor(mIoPool->GetIoService(), tcp::endpoint(tcp::v4(), mPort)));

			System::Log::Print("Running with : - 2 Network thread(s) ");
			System::Log::Print("CPU : " + std::to_string((unsigned long long)logicThreads) + " Logic thread(s)");
			System::Log::Print("");
		}
		//---------------------------------------------------------------------
		void TimeServer::Start()
		{
			// note : Order matters !
			Scale();
			Accept();

			System::Log::Print("Waiting for TimeConnections.");
			mStarted = true;

			Run();
		}
		//---------------------------------------------------------------------
		void TimeServer::Run()
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
		void TimeServer::Stop()
		{
			mStarted = false;
		}
		//---------------------------------------------------------------------
		void TimeServer::Accept()
		{
			TimeConnection::pointer session = boost::make_shared<TimeConnection>(mIoPool->GetIoService());
			mAcceptor->async_accept(session->GetSocket(),
				boost::bind(&TimeServer::HandleAccept, this,
				session, boost::asio::placeholders::error));
		}
		//---------------------------------------------------------------------
		void TimeServer::HandleAccept(TimeConnection::pointer pSession, const boost::system::error_code& pError)
		{
			if(!pError)
			{
				OnTimeConnection(pSession);
			}
			else
			{
				System::Log::Error(pError.message());
			}
			Accept();
		}
		//---------------------------------------------------------------------
		void TimeServer::OnEvent(std::shared_ptr<System::Event> pEvent)
		{
			if(!mStarted)
			{
				mGuard.unlock();
			}
		}
		//---------------------------------------------------------------------
	}
}