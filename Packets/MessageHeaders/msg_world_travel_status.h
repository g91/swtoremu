#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;

    class WorldTravelStatus : public BasicSerializable <uint32_t, uint32_t, uint32_t>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, uint32_t, Unknown)
    };
};
