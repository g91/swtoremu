#pragma once

#include <cstdint>
#include <iostream>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicContainer;

    class SignatureResponse : public BasicSerializable <uint32_t, uint32_t, uint32_t,
            BasicContainer <uint32_t, std::string>,
            BasicContainer <uint32_t, std::string>,
            BasicContainer <uint32_t, std::string>, uint64_t,
            BasicContainer <uint32_t, std::string>,
            BasicContainer <uint32_t, std::string>, uint64_t>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, uint32_t, Unknown1)
            ACCESSOR_1(3, std::string, Unknown2)
            ACCESSOR_1(4, std::string, Unknown3)
            ACCESSOR_1(5, std::string, Unknown4)
            ACCESSOR_1(6, uint64_t, Unknown5)
            ACCESSOR_1(7, std::string, Unknown6)
            ACCESSOR_1(8, std::string, Unknown7)
            ACCESSOR_1(9, uint64_t, Unknown8)
    };
};
