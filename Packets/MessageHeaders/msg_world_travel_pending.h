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

    class WorldTravelPending : public BasicSerializable <uint32_t, uint32_t,
            BasicContainer <uint32_t, std::string>, BasicContainer <uint32_t, std::string>, 
            uint64_t, uint64_t, BasicContainer <uint32_t, std::string>>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, std::string, AreaName)
            ACCESSOR_1(3, std::string, Unknown1)
            ACCESSOR_1(4, uint64_t, AreaID2)
            ACCESSOR_1(5, uint64_t, Unknown2)
            ACCESSOR_1(6, std::string, Unknown3)
    };
};
