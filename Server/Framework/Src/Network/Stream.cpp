#include <Network/Stream.h>
#include <Network/Packet.h>
#include <string>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace Swtor
{
	namespace Network
	{
        //---------------------------------------------------------------------
		Stream::Stream()
			:Byte4(false), Byte5(false), Byte6(false), Byte7(false), Byte8(false), Byte9(false), UnkType(5), UnkDwordC(0), ReplicationStreamContext(0)
		{
		}
		//---------------------------------------------------------------------
        Stream::Stream(Swtor::Network::Packet& packet, uint8_t style)
			:Byte4(false), Byte5(false), Byte6(false), Byte7(false), Byte8(false), Byte9(false), mPacket(packet), UnkType(5), UnkDwordC(0), ReplicationStreamContext(0)
		{
		}
		//---------------------------------------------------------------------
		void Stream::Initialize(uint8_t style)
		{
            Style = style;

			switch (Style)
            {
                case 1:
                    Byte4 = true;
                    Byte6 = true;
                    Byte7 = true;
                    break;

                case 2:
                    Byte4 = true;
                    Byte5 = true;
                    Byte6 = true;
                    Byte7 = true;
                    break;

                case 3:
                    Byte4 = true;
                    Byte5 = true;
                    Byte6 = true;
                    Byte7 = true;
                    Byte9 = true;
                    break;

                case 4:
                    Byte4 = true;
                    Byte6 = true;
                    Byte7 = true;
                    Byte9 = true;
                    break;

                case 5:
                    Byte4 = true;
                    Byte7 = true;
                    break;

                case 6:
                    Byte5 = true;
                    Byte7 = true;
                    break;

                case 7:
                case 8:
                    Byte6 = true;
                    Byte8 = true;
                    Byte9 = true;
                    break;

                case 9:
                case 10:
                    Byte4 = true;
                    Byte6 = true;
                    Byte9 = true;
                    break;

                case 0:
                    break;

                default:
                    throw std::out_of_range("Invalid Stream style");
            }
		}
		//---------------------------------------------------------------------
        bool Stream::ReadPackedULong(uint64_t& val)
        {
            uint8_t toRead = 0;

            uint8_t outp;
            mPacket >> outp;

            if (UnkType <= 1)
            {
                if (outp <= 127)
                {
                    val = outp;
                    return true;
                }

                if ((uint8_t)(outp + 80) <= 15)
                    toRead = outp - 175;
                else
                    return false;
            }
            else
            {
                if (outp <= 191)
                {
                    val = outp;
                    return true;
                }

                if ((uint8_t)(outp + 56) <= 7)
                    toRead = outp - 199;
                else
                    return false;
            }

            val = mPacket.ReadPacked(toRead);
            return true;
        }
        //---------------------------------------------------------------------
        bool Stream::ReadCounters(uint32_t& counter1, uint32_t& counter2)
        {
            if (Byte7)
            {
                uint64_t c1, c2;
                if (ReadPackedULong(c1) && ReadPackedULong(c2))
                {
                    counter1 = c1;
                    counter2 = c2;
                    return true;
                }
                return false;
            }

            uint64_t co;
            if (!ReadPackedULong(co))
                return false;

            counter1 = co;
            counter2 = co;
            return true;
        }
        //---------------------------------------------------------------------
        void Stream::UnknownDeserializationStart(uint8_t valueState) // TODO: a lot of todo! :)
        {
            if (valueState != 1)
                throw std::runtime_error("Invalid value state");

            if (Byte8)
            {
                uint64_t sId;
                uint64_t size;

                if (UnkDwordC != 0)
                {
                    //unk...
                }
                else
                {
                    if (!ReadPackedULong(sId))
                        throw std::runtime_error("Unable to class structure ID");
                }

                // unk ReplicationStreamContext
                if (false) //  if (!ReplicationStreamContext)
                    throw std::runtime_error("No input replication stream context set");

                if (!ReadPackedULong(size))
                    throw std::runtime_error("Unable to read data size");

                // TODO end implement it
            }
            else
            {
                uint32_t c1, c2;
                if (!ReadCounters(c1, c2))
                    throw std::runtime_error("Error getting counters");
            }
        }
        //---------------------------------------------------------------------
        bool Stream::ReadPackedLong(int64_t& val)
        {
            uint8_t toRead = 0;

            uint8_t outp;
            mPacket >> outp;

            if (UnkType <= 1)
            {
                if (outp <= 127)
                {
                    val = outp;
                    return true;
                }

                if ((uint8_t)(outp + 96) <= 15)
                    toRead = outp - 159;
                else if ((uint8_t)(outp + 112) <= 15)
                    toRead = outp - 143;
                else if (outp == 143)
                    val = -9223372036854775808ULL;

                return outp == 143;
            }
            else
            {
                if (outp <= 191)
                {
                    val = outp;
                    return true;
                }

                if ((uint8_t)(outp + 56) <= 7)
                    toRead = outp - 199;
                else if ((uint8_t)(outp + 64) > 7)
                {
                    if (outp == 208)
                        val = -9223372036854775808ULL;

                    return outp == 208;
                }

                toRead = outp - 191;
            }

            val = mPacket.ReadPacked(toRead);
            return true;
        }
        //---------------------------------------------------------------------
        bool Stream::ReadString(std::string& out)
        {
            uint8_t b;
            mPacket >> b;

            uint64_t co;

            if (UnkType <= 1)
            {
                if (b != 137 || !ReadPackedULong(co))
                {
                    out = "";
                    return false;
                }
            }
            else
                co = b;

            if (co == 0)
            {
                out = "";
                return false;
            }

            out = mPacket.ReadString(co);
            return true;
        }
        //---------------------------------------------------------------------
        bool Stream::ReadFloat(float& out)
        {
            if (UnkType > 1)
            {
                mPacket >> out;
                return true;
            }

            uint8_t b;
            mPacket >> b;

            if (b == 130)
                mPacket >> out;

            return b == 130;
        }
        //---------------------------------------------------------------------
        bool Stream::ReadBoolean(bool& out)
        {
            uint8_t b;
            mPacket >> b;

            if (UnkType <= 1)
                b = b - 128;

            if (b == 0)
                out = false;
            else if (b == 1)
                out = true;
            else
                return false;

            return true;
        }
        //---------------------------------------------------------------------
        bool Stream::ReadUnknownCounter(uint64_t& out)
        {
            uint8_t b;
            mPacket >> b;

            if ((UnkType > 1 && b != 209) || (UnkType <= 1 && b != 254))
                return false;

            return ReadPackedULong(out);
        }
        //---------------------------------------------------------------------
        bool Stream::ReadVariableId()
        {
            uint64_t out; // Hax in the client... It does not return this val (UnkType is always 5)

            if (Byte5 && UnkType < 5)
                return ReadPackedULong(out);

            return true;
        }
        //---------------------------------------------------------------------
        bool Stream::ReadType(uint64_t& out)
        {
            if (!Byte4)
                return true;

            return ReadPackedULong(out);
        }
        //---------------------------------------------------------------------
        bool Stream::ReadFieldId(int64_t& out, int64_t unk)
        {
            int64_t a;
            bool b = ReadPackedLong(a);

            if (b)
                out = a + unk;

            return b;
        }
        //---------------------------------------------------------------------
        bool Stream::ReadUnkCheckByte()
        {
            uint8_t b;
            mPacket >> b;

            return (UnkType > 1 && b == 211) || (UnkType <= 1 && b == 255);
        }
        //---------------------------------------------------------------------
        bool Stream::ReadUnkKey(uint64_t& key)
        {
            uint8_t b = mPacket.Peek();
            
            if (UnkType > 1)
            {
                if (b == 210)
                {
                    mPacket >> b;

                    std::string key; // need some unk processing (sub_47ABD0 in 1.2.0 retailclient-publictest IDB)
                    bool suc = ReadString(key);

                    if (suc)
                    {
                        // process string -> uint64_t
                    }

                    return suc;
                }
            }
            else
            {
                if (b == 137)
                {
                    std::string key; // need some unk processing (sub_47ABD0 in 1.2.0 retailclient-publictest IDB)
                    bool suc = ReadString(key);

                    if (suc)
                    {
                        // process string -> uint64_t
                    }

                    return suc;
                }
            }

            return ReadPackedULong(key);
        }
        //---------------------------------------------------------------------
        bool Stream::CheckResourceHeader(uint32_t opcode, uint16_t maxContentVersion)
        {
            if (mPacket.Opcode != opcode)
                throw std::runtime_error("CheckResourceHeader: FOURCC value doesn't match.");

            if (mPacket.ContentV < 1)
                throw std::runtime_error("CheckResourceHeader: Content format is too old, data can not be read.");

            if (mPacket.ContentV > maxContentVersion)
                throw std::runtime_error("CheckResourceHeader: Content format saved with later version of software, data can not be read.");

            if (mPacket.TransportV < 1)
                throw std::runtime_error("CheckResourceHeader: Transport format is too old, data can not be read.");

            if (mPacket.TransportV > 5)
                throw std::runtime_error("CheckResourceHeader: Transport format saved with later version of software, data can not be read.");

            return true;
        }
        //---------------------------------------------------------------------
    }
}