#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicContainer;

    class SetTrackingInfo : public BasicSerializable <uint32_t, uint32_t,
            uint64_t, uint64_t, BasicContainer <uint32_t, std::string>>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, uint64_t, AreaID)
            ACCESSOR_1(3, uint64_t, Unknown)
            ACCESSOR_1(4, std::string, AreaName)
    };
};

