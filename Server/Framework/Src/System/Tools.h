#pragma once

#include <string>
#include <Network/Packet.h>

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
	namespace System
	{
		void DECLDIR PrintBinary(unsigned char* data, int length, const std::string& pText = "");
		void DECLDIR PrintBinary(Network::Packet& pPacket);
	}
}