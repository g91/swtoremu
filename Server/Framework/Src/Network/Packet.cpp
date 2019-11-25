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
        Packet::Packet()
            :Opcode(0), ContentV(0), TransportV(0), Type(0)
        {
        }
        //---------------------------------------------------------------------
        Packet::Packet(uint32_t pOpcode, uint16_t pContentV, uint16_t pTransportV, uint8_t pType)
            :Opcode(pOpcode), ContentV(pContentV), TransportV(pTransportV), Type(pType)
        {
        }
		//---------------------------------------------------------------------
		Packet& Packet::operator<<(Packet::DataType pDataType)
		{
			mDataType = pDataType;

			return *this;
		}
		//---------------------------------------------------------------------
		Packet& Packet::operator>>(Packet::DataType pDataType)
		{
			mDataType = pDataType;

			return *this;
		}
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(bool pData)
        {
            if(pData)
                *this << uint8_t(1);
            else
                *this << uint8_t(0);

            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const uint8_t& pData)
        {
            mBuffer.append((char*)&pData, 1);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const uint16_t& pData)
        {
            mBuffer.append((char*)&pData, 2);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const uint32_t& pData)
        {
            mBuffer.append((char*)&pData, 4);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const uint64_t& pData)
        {
            mBuffer.append((char*)&pData, 8);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const float& pData)
        {
            mBuffer.append((char*)&pData, 4);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const double& pData)
        {
            mBuffer.append((char*)&pData, 8);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const std::string& pData)
        {
            if (pData.empty() || *(pData.end() - 1) != 0)
            {
                *this << (uint32_t)pData.size() + 1;
                mBuffer.append(pData.c_str(), pData.size());
                mBuffer.push_back(0);
            }
            else
            {
                *this << (uint32_t)pData.size();
                mBuffer.append(pData.c_str(), pData.size());
            }

            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator<<(const char* pData)
        {
            *this << std::string(pData);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator>>(bool& pData)
        {
            pData = bool(*(uint8_t*)&mBuffer[0]);
            mBuffer.erase(0,1);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator>>(uint8_t& pData)
        {
            pData = *(uint8_t*)&mBuffer[0];
            mBuffer.erase(0,1);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator>>(uint16_t& pData)
        {
            pData = *(uint16_t*)&mBuffer[0];
            mBuffer.erase(0,2);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator>>(uint32_t& pData)
        {
            pData = *(uint32_t*)&mBuffer[0];
            mBuffer.erase(0,4);
            return *this;
        }
		//---------------------------------------------------------------------
		Packet& Packet::operator>>(uint64_t& pData)
		{
			if(mDataType == Packet::raw)
			{
				pData = *(uint64_t*)&mBuffer[0];
				mBuffer.erase(0,8);
			}
			else
			{
				pData = ReadUVarNumeric();
			}
			return *this;
		}
		//---------------------------------------------------------------------
		Packet& Packet::operator>>(int64_t& pData)
		{
			if(mDataType == Packet::raw)
			{
				pData = *(int64_t*)&mBuffer[0];
				mBuffer.erase(0,8);
			}
			else
			{
				pData = ReadVarNumeric();
			}
			return *this;
		}
        //---------------------------------------------------------------------
        Packet& Packet::operator>>(float& pData)
        {
            pData = *(float*)&mBuffer[0];
            mBuffer.erase(0,4);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator>>(double& pData)
        {
            pData = *(double*)&mBuffer[0];
            mBuffer.erase(0,8);
            return *this;
        }
        //---------------------------------------------------------------------
        Packet& Packet::operator>>(std::string& pData)
        {
            uint32_t size;
            *this >> size;

            // Check for fake string size to prevent memory hacks
            if (size > mBuffer.size() || size <= 0)
                throw std::out_of_range("String size > packet size");

            pData = mBuffer.substr(0,size);

            if(pData[size - 1] == 0)
                pData.erase(pData.end() - 1);

            pData.shrink_to_fit();

            mBuffer.erase(0,size);
            return *this;
        }
        //---------------------------------------------------------------------
        void Packet::Write(uint8_t* pData, size_t pSize, int32_t pPos)
        {
            if(pPos < 0)
                mBuffer.append((char*)pData, pSize);
            else if(pPos + pSize <= mBuffer.size())
            {
                memcpy(&mBuffer[pPos], pData, pSize);
            }
        }
        //---------------------------------------------------------------------
        void Packet::Initialize(const std::vector<char>& pData)
        {
            mBuffer.clear();
            mBuffer.append(&pData[0], pData.size());
        }
        //---------------------------------------------------------------------
        void Packet::Initialize(const std::string& pData)
        {
            mBuffer.clear();
            mBuffer.append(&pData[0], pData.size());
        }
        //---------------------------------------------------------------------
        uint64_t Packet::ReadUVarNumeric()
        {
            // unsigned
            uint8_t num1 = *(uint8_t*)&mBuffer[0];
            mBuffer.erase(0,1);

            uint64_t value = 0UL;

            if (num1 >= 192)
            {
                if (num1 < 200 || num1 > 207)
                    return -1;

                uint8_t num2 = num1 - 199U;
                value = ReadPacked((int)num2);
            }
            else
                value = (uint64_t)num1;

            return value;
        }
        //---------------------------------------------------------------------
        int64_t Packet::ReadVarNumeric()
        {
            // signed
            uint8_t num1 = *(uint8_t*)&mBuffer[0];
            mBuffer.erase(0, 1);

            if (num1 < 192)
                return num1;

            if ((uint8_t) (num1 + 56U) > 7)
            {
                if ((uint8_t) (num1 + 64U) > 7)
                {
                    if (num1 != 208)
                        return 0UL;

                    return -9223372036854775808ULL;
                }

                return -(int64_t) ReadPacked(num1 - 191);
            }
            else
                return -(int64_t) ReadPacked(num1 - 199);
        }
        //---------------------------------------------------------------------
        uint64_t Packet::ReadPacked(int length)
        {
            uint64_t value = 0UL;
            if (length > 8)
                return value;

            std::string pData = mBuffer.substr(0, length);

            mBuffer.erase(0, length);
            for (uint8_t index = 0; (int)index < length; ++index)
                value = (value << 8) | (uint64_t)pData[(int)index];

            return value;
        }
        //---------------------------------------------------------------------
        void Packet::InitializeHeader(const std::string& pData)
        {
            Type = *(uint8_t*)&pData[0];
            Size = *(uint32_t*)&pData[1];
            mChecksum = *(uint8_t*)&pData[5];
        }
        //---------------------------------------------------------------------
        std::string Packet::GetHeader()
        {
            Finalize();

            std::string data;

            data.append((char*)&Type, 1);
            data.append((char*)&Size, 4);
            data.append((char*)&mChecksum, 1);
            data.append((char*)&Opcode, 4);
            data.append((char*)&ContentV, 2);
            data.append((char*)&TransportV, 2);

            return data;
        }
        //---------------------------------------------------------------------
        int32_t Packet::GetPosition()
        {
            return (int32_t)mBuffer.size();
        }
        //---------------------------------------------------------------------
        const std::string& Packet::GetBuffer()
        {
            return mBuffer;
        }
        //---------------------------------------------------------------------
        void Packet::Finalize()
        {
            mChecksum = Type ^ ((char*)&Size)[0] ^ ((char*)&Size)[1] ^ ((char*)&Size)[2] ^ ((char*)&Size)[3];
        }
        //---------------------------------------------------------------------
        std::string Packet::ReadString(uint32_t length)
        {
            std::string pData = mBuffer.substr(0, length);
            mBuffer.erase(0, length);

            return pData;
        }
        //---------------------------------------------------------------------
        uint8_t Packet::Peek()
        {
            return *(uint8_t*)&mBuffer[0];
        }
        //---------------------------------------------------------------------
    }
}