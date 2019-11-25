#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <Network/Packet.h>

#pragma warning(disable: 4251)

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
        class DECLDIR Stream
		{
		public:

			Stream();
            Stream(Packet& packet, uint8_t style);

			void Initialize(uint8_t style);

            bool ReadPackedULong(uint64_t& val);
            bool ReadPackedLong(int64_t& val);
            bool ReadCounters(uint32_t& counter1, uint32_t& counter2);
            bool ReadString(std::string& out);
            bool ReadFloat(float& out);
            bool ReadBoolean(bool& out);
            bool ReadUnknownCounter(uint64_t& out);

            bool ReadVariableId();
            bool ReadType(uint64_t& out);
            bool ReadFieldId(int64_t& out, int64_t unk);

            bool ReadUnkCheckByte();
            bool ReadUnkKey(uint64_t& key);

            bool CheckResourceHeader(uint32_t opcode, uint16_t maxContentVersion);

            void UnknownDeserializationStart(uint8_t valueState); // Used in ClientReplicationTransaction and CreateCharacterRequest and CharacterList

			uint8_t  Style;
            uint16_t UnkType;
			Packet mPacket;
            bool Byte4; // Has Type
            bool Byte5; // Has Variable Id
            bool Byte6;
            bool Byte7;
            bool Byte8;
            bool Byte9;
            uint32_t UnkDwordC;
            uint32_t ReplicationStreamContext;
		};
    }
}