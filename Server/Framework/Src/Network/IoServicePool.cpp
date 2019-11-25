#include <Network/IoServicePool.h>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace Swtor
{
	namespace Network
	{
		//---------------------------------------------------------------------
		IoServicePool::IoServicePool(std::size_t pool_size)
			: mNextIndex(0)
		{
			if (pool_size == 0)
				throw std::runtime_error("IoServicePool size is 0");

			for (std::size_t i = 0; i < pool_size; ++i)
			{
				io_service_ptr io_service(new boost::asio::io_service);
				work_ptr work(new boost::asio::io_service::work(*io_service));
				mIoServices.push_back(io_service);
				mWork.push_back(work);
			}
		}
		//---------------------------------------------------------------------
		void IoServicePool::Run()
		{
			// Create a pool of threads to run all of the io_services.
			for (std::size_t i = 0; i < mIoServices.size(); ++i)
			{
				boost::shared_ptr<boost::thread> thread(new boost::thread(
					[this,i]()
				{
					boost::timer timer;
					while(!mIoServices[i]->stopped())
					{
						timer.restart();

						mIoServices[i]->poll();
						mIoServices[i]->reset();

						uint32_t elapsed = std::uint32_t(timer.elapsed() * 1000);

						if(elapsed < 50){
							boost::this_thread::sleep(boost::posix_time::milliseconds(50 - elapsed));
						}
					}
				}));
				mThreads.push_back(thread);
			}
		}
		//---------------------------------------------------------------------
		void IoServicePool::Stop()
		{
			// Explicitly Stop all io_services.
			for (std::size_t i = 0; i < mIoServices.size(); ++i)
				mIoServices[i]->stop();

			for (std::size_t i = 0; i < mThreads.size(); ++i)
				mThreads[i]->join();
		}
		//---------------------------------------------------------------------
		boost::asio::io_service& IoServicePool::GetIoService()
		{
			// Use a round-robin scheme to choose the next io_service to use.
			boost::asio::io_service& io_service = *mIoServices[mNextIndex];
			++mNextIndex;
			if (mNextIndex == mIoServices.size())
				mNextIndex = 0;
			return io_service;
		}
		//---------------------------------------------------------------------
	}
}