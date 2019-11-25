#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <boost/thread.hpp>

#if defined(WIN32)
#if defined FRAMEWORK_EXPORTS
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
#else
#define DECLDIR
#endif

using namespace std;

namespace Swtor { namespace System
{
	class DECLDIR Log
	{
	public:

		enum Level
		{
			NONE,
			LOW,
			VERBOSE
		};

		static Log* GetInstance();
		static void Create(const std::string& pName);

		void DoPrint(const char* pMessage, size_t pLength);
		void DoDebug(const char* pMessage, size_t pLength);
		void DoError(const char* pMessage, size_t pLength);

		void DoSetLevel(Level pLevel);
		void DoFlush();

				/**
		 * Overrides for std::string
		 */

		static inline void Print(const string& pMessage)
		{
			GetInstance()->DoPrint(pMessage.c_str(), pMessage.length());
		}
		static inline void Debug(const string& pMessage)
		{
			GetInstance()->DoDebug(pMessage.c_str(), pMessage.length());
		}
		static inline void Error(const string& pMessage)
		{
			GetInstance()->DoError(pMessage.c_str(), pMessage.length());
		}

		/**
		 * Template overrides for static strings
		 */

	template<size_t Size>
		static inline void Print(const char (&pMessage)[Size])
		{
			GetInstance()->DoPrint(pMessage, Size);
		}
	template<size_t Size>
		static inline void Debug(const char (&pMessage)[Size])
		{
			GetInstance()->DoDebug(pMessage, Size);
		}
	template<size_t Size>
		static inline void Error(const char (&pMessage)[Size])
		{
			GetInstance()->DoError(pMessage, Size);
		}

		/**
		 * Overrides for regular strings
		 */

		static inline void Print(const char* pMessage)
		{
			GetInstance()->DoPrint(pMessage, strlen(pMessage));
		}
		static inline void Debug(const char* pMessage)
		{
			GetInstance()->DoDebug(pMessage, strlen(pMessage));
		}
		static inline void Error(const char* pMessage)
		{
			GetInstance()->DoError(pMessage, strlen(pMessage));
		}

		static inline void SetLevel(Level pLevel)
		{
			GetInstance()->DoSetLevel(pLevel);
		}

		static inline void Flush()
		{
			GetInstance()->DoFlush();
		}

	private:

		Log(const std::string& pName = "WorldServer.log");
		void AppendLine(const char* pData, size_t pLength);
		void AppendData(const char* pData, size_t pLength);
		void AppendTime();

		std::vector<char> mBuffer;
		boost::mutex mLock;

		std::ofstream mLog;
		Level mLevel;

		static Log* mInstance;
	};
}
}