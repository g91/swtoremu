#pragma once

#include <cstdint>
#include <iostream>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicVector;

    class CharacterListRequest : public BasicSerializable <uint32_t, uint32_t>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
    };
};

