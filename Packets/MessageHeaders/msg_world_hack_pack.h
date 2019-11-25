#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::CheckedFrame;
    using Serialization::BasicArray;

    class WorldHackPackDetail : public BasicSerializable <uint32_t, uint32_t, uint32_t, uint32_t>
    {
        public:
            ACCESSOR_1(0, uint32_t, Unknown1)
            ACCESSOR_1(1, uint32_t, Unknown2)
            ACCESSOR_1(2, uint32_t, Unknown3)
            ACCESSOR_1(3, uint32_t, Unknown4)
    };

    class WorldHackPack : public BasicSerializable <uint32_t, uint32_t, CheckedFrame <uint32_t, BasicArray <54, WorldHackPackDetail>>>
    {
        public:
            using Array54 = std::array <WorldHackPackDetail, 54>;
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, Array54, HackData)
    };
};
