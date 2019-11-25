#pragma once

#include <string>

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
	namespace Crypt
	{
		class DECLDIR RSA
		{
		public:

			/**
			 * Decrypt RSA data
			 * @param pBuffer The buffer to decrypt
			 * @return The decrypted data
			 */
			static std::string Decrypt(const std::string& pBuffer);
		};
	}
}