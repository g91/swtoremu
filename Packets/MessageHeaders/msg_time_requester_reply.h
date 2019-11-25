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

    class TimeRequesterReply : public BasicSerializable <uint32_t, uint32_t,
            BasicContainer <uint32_t, std::string>, uint32_t, BasicVector <uint32_t, uint8_t>>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, std::string, Address)
            ACCESSOR_1(3, uint32_t, Port)
            ACCESSOR_1(4, std::vector <uint8_t>, Payload)
    };
};
