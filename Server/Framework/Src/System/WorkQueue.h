#pragma once

#include <System/Job.h>
#include <boost/thread.hpp>
#include <list>
#include <queue>

#if defined(WIN32)
#if defined FRAMEWORK_EXPORTS
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
#else
#define DECLDIR
#endif

namespace Swtor{
	namespace System
	{
		class DECLDIR WorkQueue
		{
		public:

			WorkQueue(unsigned int pThreadCount);
			~WorkQueue();

			void Run();

			void Add(Job* task);

		private:
			boost::mutex mLock;
			std::queue<Job*> mJobs;
			std::list<std::shared_ptr<boost::thread>> mThreads;
		};
	}
}