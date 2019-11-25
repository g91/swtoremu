#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/switched_serializable.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::SwitchedSerializable;
    using Serialization::BasicSerializable;
    using Serialization::SwitchedField;
    using Serialization::BasicArray;

    class PlayerMoveState : public BasicSerializable <uint32_t, uint32_t,
            SwitchedSerializable <uint16_t,
                SwitchedField <0x0001, float>,
                SwitchedField <0x0002, BasicArray <3, float>>,
                SwitchedField <0x0020, float>,
                SwitchedField <0x0004, BasicArray <3, float>>,
                SwitchedField <0x0008, uint8_t>,
                SwitchedField <0x0010, uint8_t>,
                SwitchedField <0x0040, uint64_t>,
                SwitchedField <0x0080, uint64_t>,
                SwitchedField <0x0100, uint64_t>,
                SwitchedField <0x0200, BasicArray <3, float>>>,
            BasicArray <2, uint8_t>>
    {
        public:
            using Pad = std::array <uint8_t, 2>;
            using Vec3 = std::array <float, 3>;
            ACCESSOR_1(0,      uint32_t, MessageID)
            ACCESSOR_1(1,      uint32_t, StreamID)
            ACCESSOR_2(2, 0,   float, Heading)
            ACCESSOR_2(2, 1,   Vec3, MoveVec)
            ACCESSOR_2(2, 2,   float, Jump)
            ACCESSOR_2(2, 3,   Vec3, EndPosition)
            ACCESSOR_2(2, 4,   uint8_t, Forward)
            ACCESSOR_2(2, 5,   uint8_t, Warp)
            ACCESSOR_2(2, 6,   uint64_t, LastTransactionID)
            ACCESSOR_2(2, 7,   uint64_t, SyncTime)
            ACCESSOR_2(2, 8,   uint64_t, Platform)
            ACCESSOR_2(2, 9,   Vec3, PlatformOffset)
            ACCESSOR_1(3,      Pad, Padding)
    };
};
