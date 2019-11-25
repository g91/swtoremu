#pragma once

#include <DAO/DAO.h>

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
		class DECLDIR DBWorkQueue
		{
		public:

			enum Type{
				SAVE,
				LOAD
			};

			DBWorkQueue(const std::string& pDSN, unsigned int pThreadCount);
			~DBWorkQueue();

			void Run();

			void Push(boost::shared_ptr<DAO::IDAO> pObject);

		private:

			boost::mutex mLock;
			const std::string mDSN;
			std::queue<boost::shared_ptr<DAO::IDAO>> mJobs;
			std::list<boost::shared_ptr<boost::thread>> mThreads;
		};
	}
}