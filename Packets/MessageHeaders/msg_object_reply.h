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

    class ObjectReply : public BasicSerializable <uint32_t, uint32_t, uint16_t,
            BasicContainer <uint32_t, std::string>,
            BasicContainer <uint32_t, std::string>,
            BasicContainer <uint32_t, std::string>, uint64_t>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, uint16_t, Unknown1)
            ACCESSOR_1(3, std::string, Unknown2)
            ACCESSOR_1(4, std::string, Unknown3)
            ACCESSOR_1(5, std::string, Unknown4)
            ACCESSOR_1(6, uint64_t, Unknown5)
    };
};

