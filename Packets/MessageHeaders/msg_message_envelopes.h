#pragma once

#include <cstdint>
#include <string>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicContainer;
    using Serialization::BasicVector;

    class MessageEnvelopesDetail : public BasicSerializable <
            uint64_t, uint16_t, uint64_t, uint64_t,
            BasicContainer <uint32_t, std::string>, 
            BasicContainer <uint32_t, std::string>,
            uint64_t, uint64_t, uint64_t, uint64_t, uint8_t,
            BasicContainer <uint32_t, std::string>,
            uint64_t, uint16_t>
    {
        public:
            ACCESSOR_1(0, uint64_t, Unknown1)
            ACCESSOR_1(1, uint16_t, Unknown2)
            ACCESSOR_1(2, uint64_t, Unknown3)
            ACCESSOR_1(3, uint64_t, Unknown4)
            ACCESSOR_1(4, std::string, Unknown5)
            ACCESSOR_1(5, std::string, Unknown6)
            ACCESSOR_1(6, uint64_t, Unknown7)
            ACCESSOR_1(7, uint64_t, Unknown8)
            ACCESSOR_1(8, uint64_t, Unknown9)
            ACCESSOR_1(9, uint64_t, Unknown10)
            ACCESSOR_1(10, uint8_t, Unknown11)
            ACCESSOR_1(11, std::string, Unknown12)
            ACCESSOR_1(12, uint64_t, Unknown13)
            ACCESSOR_1(13, uint16_t, Unknown14)
    };

    class MessageEnvelopes : public BasicSerializable <uint32_t, uint32_t, BasicVector <uint32_t, MessageEnvelopesDetail>>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, std::vector <MessageEnvelopesDetail>, Envelopes)
    };
};

