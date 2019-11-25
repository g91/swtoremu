#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicVector;

    class Message_0x8eb28de9 : public BasicSerializable <uint32_t, uint32_t, BasicVector <uint32_t, uint8_t>>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, std::vector <uint8_t>, Payload)
    };
};

