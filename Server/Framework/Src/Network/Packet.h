#pragma once

#include <cstdint>
#include <vector>
#include <string>

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

// Common segment
namespace Opcode
{
    typedef const uint32_t __opcode;

    static __opcode MSG_REQUEST_SIGNATURE               = 0xA609E6A7;
    static __opcode MSG_SIGNATURE                       = 0x6731C5AF;
}

// Client segment
namespace Opcode
{
    // Proxy server
    static __opcode CMSG_REQUEST_INTRODUCE_CONNECTION   = 0x8B0D492F;
    // Game server
    // General opcodes
    static __opcode CMSG_SERVICE_REQUEST                = 0x5FE920D4;
    static __opcode CMSG_REQUEST_CLOSE                  = 0x43DB3479;
    static __opcode CMSG_LIST_MODULES                   = 0x2195CC8A;
    static __opcode CMSG_TIME_SERVER_REQUEST            = 0x420923E0;
    static __opcode CMSG_GAME_STATE                     = 0xD0D38F43;
    static __opcode CMSG_WORLD_HACKNOTIFY               = 0x0C0BA34F;
    static __opcode CMSG_ERROR_DEBUG                    = 0x9ab71e5;
    // Area opcodes
    static __opcode CMSG_AREA_MODULE_LIST               = 0x74D16DED;
    // Character opcodes
    static __opcode CMSG_CHARACTER_LIST                 = 0xFB2047CE;
    static __opcode CMSG_CHARACTER_CREATE               = 0xD130EAB9;
    static __opcode CMSG_CHARACTER_SELECT               = 0xCFFE7758;
    static __opcode CMSG_CHARACTER_DELETE               = 0xD006BAE0;
    static __opcode CMSG_CHARACTER_SOMETHING            = 0xC26464A9;
    static __opcode CMSG_CHARACTER_SYNC                 = 0x61116AD5;
    // Unknown
    static __opcode CMSG_UNK_34287945                   = 0x34287945;
    static __opcode CMSG_UNK_C26464A9                   = 0xC26464A9;
    static __opcode CMSG_UNK_8C6422C1                   = 0x8C6422C1;
    static __opcode CMSG_UNK_A4BCD6F2                   = 0xA4BCD6F2;
    static __opcode CMSG_UNK_7DAA9F08                   = 0x7DAA9F08;
    static __opcode CMSG_UNK_3E7D74F5                   = 0x3E7D74F5;
    static __opcode CMSG_UNK_463B0D17                   = 0x463B0D17;
    static __opcode CMSG_UNK_B4BF82C3                   = 0xB4BF82C3;
    static __opcode CMSG_UNK_8A2B911C                   = 0x8A2B911C;
    static __opcode CMSG_UNK_54846FBB                   = 0x54846FBB;
    static __opcode CMSG_UNK_CA2408CA                   = 0xCA2408CA;
    static __opcode CMSG_UNK_74361BD6                   = 0x74361BD6;
    static __opcode CMSG_UNK_45F77B86                   = 0x45F77B86;
    static __opcode CMSG_UNK_9FF5CB09                   = 0x9FF5CB09;
    static __opcode CMSG_UNK_65662EE3                   = 0x65662EE3;
    static __opcode CMSG_UNK_E00561B1                   = 0xE00561B1;
    static __opcode CMSG_UNK_CA2CD23C                   = 0xCA2CD23C;
    static __opcode CMSG_UNK_874B000B                   = 0x874B000B;
    static __opcode CMSG_UNK_E6779198                   = 0xE6779198;
    static __opcode CMSG_UNK_6B5AE34F                   = 0x6B5AE34F;
    static __opcode CMSG_UNK_13831C74                   = 0x13831C74;
    static __opcode CMSG_UNK_8EB28DE9                   = 0x8EB28DE9;
    static __opcode CMSG_UNK_41D98BE4                   = 0x41D98BE4;
    static __opcode CMSG_UNK_F96DCDB0                   = 0xF96DCDB0;
    static __opcode CMSG_UNK_24237B20                   = 0x24237B20;
    static __opcode CMSG_UNK_ABDD361B                   = 0xABDD361B;
    static __opcode CMSG_UNK_C586BD22                   = 0xC586BD22;
    static __opcode CMSG_UNK_CCACB51D                   = 0xCCACB51D;
    static __opcode CMSG_UNK_7CB9A193                   = 0x7CB9A193;
    static __opcode CMSG_UNK_CC0EE201                   = 0xCC0EE201;
    static __opcode CMSG_UNK_FC5428CF                   = 0xFC5428CF;
    static __opcode CMSG_UNK_62DAF193                   = 0x62DAF193;
    static __opcode CMSG_UNK_94FE0EC5                   = 0x94FE0EC5;
    static __opcode CMSG_UNK_ADD30040                   = 0xADD30040;
    static __opcode CMSG_UNK_F868A7B2                   = 0xF868A7B2;
    static __opcode CMSG_UNK_4D0E265F                   = 0x4D0E265F;
    static __opcode CMSG_UNK_DB0AC09C                   = 0xDB0AC09C;
    static __opcode CMSG_UNK_E29C3D37                   = 0xE29C3D37;
    static __opcode CMSG_UNK_4A765897                   = 0x4A765897;
    static __opcode CMSG_UNK_E32955EB                   = 0xE32955EB;
    static __opcode CMSG_UNK_5A249BE7                   = 0x5A249BE7;
    static __opcode CMSG_UNK_89193FFC                   = 0x89193FFC;
    static __opcode CMSG_UNK_5D9D6735                   = 0x5D9D6735;
    static __opcode CMSG_UNK_EA9C92F3                   = 0xEA9C92F3;
    static __opcode CMSG_UNK_10C3908A                   = 0x10C3908A;
    static __opcode CMSG_UNK_32A8F7BE                   = 0x32A8F7BE;
    static __opcode CMSG_UNK_C922FBED                   = 0xC922FBED;
    static __opcode CMSG_UNK_8AF20DBA                   = 0x8AF20DBA;
    static __opcode CMSG_UNK_9F397942                   = 0x9F397942;
    static __opcode CMSG_UNK_A79A231A                   = 0xA79A231A;
    static __opcode CMSG_UNK_50EC2009                   = 0x50EC2009;
    static __opcode CMSG_UNK_952507AA                   = 0x952507AA;
    static __opcode CMSG_UNK_F45B53BA                   = 0xF45B53BA;
    static __opcode CMSG_UNK_51126689                   = 0x51126689;
    static __opcode CMSG_UNK_09AB71E5                   = 0x09AB71E5;
    static __opcode CMSG_UNK_69A1C6B6                   = 0x69A1C6B6;
    static __opcode CMSG_UNK_BD7386AC                   = 0xBD7386AC;
    static __opcode CMSG_UNK_78E5EA4D                   = 0x78E5EA4D;
    static __opcode CMSG_UNK_332E14F7                   = 0x332E14F7;
    static __opcode CMSG_UNK_8FDD458A                   = 0x8FDD458A;
    static __opcode CMSG_UNK_817174C3                   = 0x817174C3;
    static __opcode CMSG_UNK_453174C6                   = 0x453174C6;
    static __opcode CMSG_UNK_3E11A62A                   = 0x3E11A62A;
    static __opcode CMSG_UNK_AF809BB0                   = 0xAF809BB0;
}

// Server segment
namespace Opcode
{
    // Proxy server
    static __opcode SMSG_REQUEST_INTRODUCE_CONNECTION   = 0x90F2D084;
    // Game server
    // General opcodes
    static __opcode SMSG_SIGNATURE_RESPONSE             = 0x8B0D492F;
    static __opcode SMSG_CLIENT_INFORMATION             = 0xD4BA5CFB;
    static __opcode SMSG_TIME_SERVER_REPLY              = 0x8D576F7B;
    static __opcode SMSG_TALK_2                         = 0xF6C50FB3;
    // Area opcodes
    static __opcode SMSG_CLIENT_REPLICATION_TRANSACTION = 0x0D446E80;
    static __opcode SMSG_TALK                           = 0x6BA87A93;
    static __opcode SMSG_SET_CHARACTER                  = 0xCFBFFBCB;
    
    static __opcode SMSG_AWARENESS_ENTERED              = 0xA1D9E226;
    static __opcode SMSG_UPDATE_TIME_SOURCE             = 0x8F0A39AA;
    // Character opcodes
    static __opcode SMSG_CHARACTER_LIST                 = 0x0EC2A425; // SMSG_TELL_CHARACTER_SUMMARIES
    static __opcode SMSG_CHARACTER_REJECT_NEW           = 0x5A4151FC;
    static __opcode SMSG_CHARACTER_SELECTED             = 0xA0D00B3A;
    static __opcode SMSG_TRAVEL_PENDING                 = 0x246462DB;
    static __opcode SMSG_TRAVEL_STATUS                  = 0x7AD491DA;
    static __opcode SMSG_SEND_TO_AREA                   = 0x13509F15;
    static __opcode SMSG_CHARACTER_TELEPORT             = 0x944511BF;
    static __opcode SMSG_CHARACTER_REJECT_SELECTION     = 0xEC510F46;

    // Service opcodes
    static __opcode SMSG_GAME_REPLICATION_TRANSACT      = 0x34287945; // SMSG_CLIENT_REPLICATION_TRANSACTION_2

    // Mailbox opcodes
    static __opcode SMSG_SET_MAILBOX_INTERACTION        = 0x01837678;
    static __opcode SMSG_MAILBOX_HAS_MAIL               = 0x4AA61E6B;
    static __opcode SMSG_CREATE_RESPONSE                = 0x4C8A105D;
    static __opcode SMSG_PAY_COD_RESPONSE               = 0x3BAE5D45;
    static __opcode SMSG_MESSAGE_TEXT                   = 0x152D0441;
    static __opcode SMSG_EXTRACT_ATTACHMENTS_RESPONSE   = 0x9AB6AF86;
    static __opcode SMSG_DELETE_RESPONSE                = 0x7D7EC34C;
    static __opcode SMSG_MESSAGE_TEXT_FAILURE           = 0x8F8D4F73;
    static __opcode SMSG_MESSAGE_ENVELOPES              = 0xC4F01C82;

    static __opcode SMSG_RECV_CHAT_MESSAGE              = 0xB5F01761;
    static __opcode SMSG_SHOULD_SEND_MISSING_ASSETS     = 0x04CCE2BB;
    // RPC opcodes
    static __opcode SMSG_WORLD_RPC                      = 0x25E86D5C; // SMSG_REQUEST_RPC_2
    static __opcode SMSG_REQUEST_RPC                    = 0x0ADFF9BF;
    static __opcode SMSG_REQUEST_MULTIPLE_RPC           = 0x23B61238;
    // Options opcodes
    static __opcode SMSG_AWARENESS_RANGE                = 0x1CA72F2D;
    // System opcodes
    static __opcode SMSG_NOTIFY_GAUNTLET_VERSION        = 0x25ACBEF4;
    static __opcode SMSG_SHOULD_SEND_SCRIPT_ERRORS      = 0x35BEBAA5;
    static __opcode SMSG_WORLD_HACK_PACK                = 0xECB59833;
    static __opcode SMSG_NOTIFY_ID                      = 0x4BD75535;
    // Unknown opcodes
    static __opcode SMSG_UNK_34287945                   = 0x34287945;
    static __opcode SMSG_UNK_A93588B6                   = 0xA93588B6;
    static __opcode SMSG_UNK_2CFF5704                   = 0x2CFF5704;
    static __opcode SMSG_UNK_4C373702                   = 0x4C373702;
    static __opcode SMSG_UNK_6CEFFD28                   = 0x6CEFFD28;
    static __opcode SMSG_UNK_43DB3479                   = 0x43DB3479;
    static __opcode SMSG_UNK_0598D9A7                   = 0x0598D9A7;


    static __opcode SMSG_EDIT_COMMAND                   = 0xD3DA98F0;
    static __opcode SMSG_EDIT_BINARY_COMMAND            = 0x6AFFFFB1;
    static __opcode SMSG_SET_BEHAVIOR                   = 0x035C75FE;
    static __opcode SMSG_CHARACTER_CHANGE_STATE         = 0xADEAFCA3;
    static __opcode SMSG_LOG_INFO                       = 0xE587F29A;
    static __opcode SMSG_LOG_DEBUG                      = 0x10FF67AB;
    static __opcode SMSG_LOG_WARNING                    = 0x8EBB0A67;
    static __opcode SMSG_LOG_ERROR                      = 0xD105177D;
    static __opcode SMSG_AREA_HACK_DATA_REQUEST         = 0xBBC9DC07;
    static __opcode SMSG_EFFEVENT_MESSAGE               = 0xDBF41C90;
    static __opcode SMSG_AWARENESS_EXITED               = 0xFEE87C7C;
    static __opcode SMSG_RENAME_ACCOUNT_LEGACY_NAME_STATUS = 0x9553F230;
    static __opcode SMSG_ID_BATCH                       = 0xAB69A205;
    static __opcode SMSG_CLI                            = 0x2F37A18B;
    static __opcode SMSG_CHARACTER_SET_RENDEZVOUS_POINT = 0x2B4792AE;
    static __opcode SMSG_AREA_DISCONNECT                = 0x30CCCB47;
    static __opcode SMSG_ASSET_CREATED                  = 0x699FAC0E;
    static __opcode SMSG_AREA_HACK_PACK                 = 0x0E71623B;
    static __opcode SMSG_CHARACTER_RENAME_STATUS        = 0x657A1AB0;
    static __opcode SMSG_SERVER_SCRIPT_ORG              = 0x020D909C;
    static __opcode SMSG_RENAME_ACCOUNT_LEGACY_NAME_STATUS_2 = 0x02E99FED;
    static __opcode SMSG_NOTIFY_AREA_DIED               = 0xE8CE387E;
    static __opcode SMSG_SEND_TO_CHARACTER_SELECT       = 0x77425A47;
    static __opcode SMSG_NOTIFY_AREA_MOVE_DENIED        = 0x83A71D32;
    static __opcode SMSG_WORLD_CLI                      = 0xEB73EF7D;
    static __opcode SMSG_SCRIPT_ERROR                   = 0xF7363BE2;
    static __opcode SMSG_CHARACTER_DELETE_STATUS        = 0xCE2B551F;
    static __opcode SMSG_CLIENT_SCRIPT_ORG              = 0xE278CDBD;
    static __opcode SMSG_WORLD_HACK_DATA_REQUEST        = 0x4E9CCAE9;
    static __opcode SMSG_ADMIN_MESSAGE                  = 0x4CD0AB5D;
    static __opcode SMSG_REJECT_ACCOUNT_CONNECTION      = 0x5BD9E9C4;
    static __opcode SMSG_REQUEST_MULTIPLE_RPC_2         = 0x1A307EB3;
    static __opcode SMSG_RESULTS                        = 0xD5280283;
    static __opcode SMSG_REQUEST_MULTIPLE_RPC_3         = 0x3886D510;
    static __opcode SMSG_REQUEST_RPC_3                  = 0x2D0B9303;
    static __opcode SMSG_TALK_3                         = 0x711700A7;
    static __opcode SMSG_RECEIVE_CHANNEL_ALERT          = 0xAFAC8A3A;
    static __opcode SMSG_TELL_CHANNELS                  = 0xB4393EE4;
    static __opcode SMSG_TELL_CHANNEL_USERS             = 0xBC9A57B6;
    static __opcode SMSG_RECEIVE_ALERT                  = 0xE03AD9F5;
    static __opcode SMSG_SEARCH_ON_RESULT               = 0x02DEFA88;
    static __opcode SMSG_SEARCH_ON_READY                = 0x783FA7D0;
    static __opcode SMSG_ENABLE_BIOMON_METRIC           = 0x48F6350F;
    static __opcode SMSG_SHOULD_SEND_SCRIPT_ERRORS_2    = 0x12E4D236;
    static __opcode SMSG_ENABLE_BIOMON_SAMPLING         = 0x6BE60540;
    static __opcode SMSG_SET_BIOMON_BAND_FREQUENCY      = 0xA2A64753;

    static __opcode SMSG_GET_DATA_REPLY_MULTIPART       = 0x789A5F34;
    static __opcode SMSG_CREATE_DIRECTORY_REPLY         = 0x33E3FD86;
    static __opcode SMSG_ADD_RESOURCE_REPLY             = 0x127D6B58;
    static __opcode SMSG_REGISTRATION_RESPONSE          = 0x26959B72;
    static __opcode SMSG_GET_DATA_REPLY                 = 0x2F7A6A25;
    static __opcode SMSG_GET_DIRECTORY_LIST_REPLY       = 0xCCDE84AB;
    static __opcode SMSG_NOTIFY_DATABASE_IMPORT_VERSION = 0xA08C1ACF;
    static __opcode SMSG_REMOVE_DIRECTORY_REPLY         = 0xA0F3186B;
    static __opcode SMSG_GET_DATA_REPLY_MULTIPART_BEGIN = 0xBD13C7FD;
    static __opcode SMSG_ANNOUNCE_UPDATE_BATCH          = 0xE5077673;
    static __opcode SMSG_GET_DATA_REPLY_END             = 0xE8379100;
    static __opcode SMSG_ANNOUNCE_WATCH                 = 0x70099AA9;
    static __opcode SMSG_REMOVE_RESOURCE_REPLY          = 0x744DED99;

    static __opcode SMSG_COMPILER_ERROR                 = 0x7808097A;
    static __opcode SMSG_COMPILE_SUCCEEDED              = 0x104C3923;
    static __opcode SMSG_SCRIPT_DEFINITIONS             = 0x18DD03BF;
    static __opcode SMSG_ERROR_MESSAGE                  = 0x30A9DB20;
    static __opcode SMSG_CLI_RESPONSE                   = 0x82DE79A1;
    static __opcode SMSG_SCRIPT_SOURCE                  = 0x983FEFFA;
    static __opcode SMSG_SCRIPT_REVISION_HISTORY        = 0xDA4ADF75;
}
    

// Packet type
namespace Opcode
{
    static __opcode CMSG_PACKET                         = 0x0;
    static __opcode SMSG_PACKET                         = 0x0;
    static __opcode CMSG_PING                           = 0x1;
    static __opcode SMSG_PING                           = 0x2;
    static __opcode SMSG_HANDSHAKE                      = 0x3;
    static __opcode CMSG_HANDSHAKE                      = 0x4;
}

namespace Swtor
{
    namespace Network
    {
        class DECLDIR Packet
        {
        public:

			enum DataType
			{
				raw, packed
			};

            Packet();
            /**
             * Construct a packet.
             * @param pOpcode Opcode to send.
             * @param pContentV The Content Version.
             * @param pTransportV The Transport Version.
             * @param pType The packet's type (ping, handshake or packet).
             */
            Packet(uint32_t pOpcode, uint16_t pContentV, uint16_t pTransportV, uint8_t pType = 0x00);

			Packet& operator<<(DataType pDataType);
			Packet& operator>>(DataType pDataType);

            Packet& operator<<(bool pData);
            Packet& operator<<(const uint8_t& pData);
            Packet& operator<<(const uint16_t& pData);
            Packet& operator<<(const uint32_t& pData);
            Packet& operator<<(const uint64_t& pData);
            Packet& operator<<(const float& pData);
            Packet& operator<<(const double& pData);
            Packet& operator<<(const std::string& pData);
            Packet& operator<<(const char* pData);

            Packet& operator>>(bool& pData);
            Packet& operator>>(uint8_t& pData);
            Packet& operator>>(uint16_t& pData);
            Packet& operator>>(uint32_t& pData);
            Packet& operator>>(uint64_t& pData);
			Packet& operator>>(int64_t& pData);
            Packet& operator>>(float& pData);
            Packet& operator>>(double& pData);
            Packet& operator>>(std::string& pData);

            void InitializeHeader    (const std::string& pData);
            void Initialize            (const std::vector<char>& pData);
            void Initialize            (const std::string& pData);
            void Write                (uint8_t* pData, size_t pSize, int32_t pPos = -1);

            uint8_t Peek();
            int32_t GetPosition();
            uint64_t ReadUVarNumeric();
            int64_t ReadVarNumeric();
            uint64_t ReadPacked(int length);
            std::string ReadString(uint32_t length);

            std::string            GetHeader();
            const std::string&     GetBuffer();

            void Finalize();

            uint8_t  Type;
            uint32_t Size;
            uint32_t Opcode;
            uint16_t ContentV;
            uint16_t TransportV;

        protected:

            std::string                    mBuffer;
            uint8_t                        mChecksum;
			DataType					   mDataType;
        };
    }
}