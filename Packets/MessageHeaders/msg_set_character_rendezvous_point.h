#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicArray;

    class SetCharacterRendezvousPoint : public BasicSerializable <uint32_t, uint32_t,
            uint64_t, uint32_t, BasicArray <3, float>, BasicArray <3, float>, uint8_t>
    {
        public:
            using Vec3 = std::array <float, 3>;
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, uint64_t, UnitID)
            ACCESSOR_1(3, uint32_t, Unknown1)
            ACCESSOR_1(4, Vec3, Unknown2)
            ACCESSOR_1(5, Vec3, Unknown3)
            ACCESSOR_1(6, uint8_t, Unknown4)
    };
};

