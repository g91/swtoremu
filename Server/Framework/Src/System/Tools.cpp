#include <System/Tools.h>
#include <System/Log.h>
#include <cstdio>
#include <sstream>

namespace Swtor
{
	namespace System
	{
		void PrintBinary(Network::Packet& pPacket)
		{
			PrintBinary((unsigned char*)&pPacket.GetBuffer()[0], pPacket.GetBuffer().size(), "");
		}
		void PrintBinary(unsigned char* data, int length, const std::string& pText)
		{
			std::ostringstream os;
			os << pText << "\n";
			size_t len = (length / 16) * 16 + 16;
			for (size_t i = 0; i < len; ++i)
			{
				if(i < length)
				{
					char buf[100];
					sprintf(buf, "%02X", data[i]);
					os << buf[0] << buf[1] << ' ';
				}
				else
				{
					os << "   ";
				}

				if((i + 1) % 16 == 0)
				{
					os << " | ";
					for(size_t j = i - 15; j <= i && j < length ; ++j)
					{
						if(data[j] > 31 && data[j] < 127)
							os << data[j];
						else
							os << ".";
					}

					os << std::endl;
				}
				else if((i + 1) % 8 == 0)
					os << "  ";
			}
			os << "\n";

			System::Log::GetInstance()->Debug(os.str());
		}
	}
}
