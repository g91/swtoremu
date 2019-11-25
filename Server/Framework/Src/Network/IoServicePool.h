#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>
#include <cstdint>

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
		class DECLDIR IoServicePool
			: private boost::noncopyable
		{
		public:
			explicit IoServicePool(std::size_t pool_size);

			void Run();

			void Stop();

			boost::asio::io_service& GetIoService();

		private:
			typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
			typedef boost::shared_ptr<boost::asio::io_service::work> work_ptr;

			std::vector<io_service_ptr> mIoServices;
			std::vector<work_ptr> mWork;
			std::vector<boost::shared_ptr<boost::thread> > mThreads;

			std::size_t mNextIndex;
		};
	}
}