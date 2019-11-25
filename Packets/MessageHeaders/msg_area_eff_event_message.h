#pragma once

#include <cstdint>
#include <string>

#include "../serialization/common_macros.h"
#include "../serialization/switched_serializable.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::SwitchedSerializable;
    using Serialization::BasicSerializable;
    using Serialization::SwitchedField;
    using Serialization::BasicVector;
    using Serialization::BasicArray;
    using Serialization::BasicContainer;
    using Serialization::CheckedFrame;
    using Serialization::Padding;

    class AreaEffEventMessageAction : public BasicSerializable <
            uint8_t, BasicContainer <uint32_t, std::string>, uint8_t,
            SwitchedSerializable <uint16_t,
                SwitchedField <0x0001, float>,
                SwitchedField <0x0002, float>,
                SwitchedField <0x0004, float>,
                SwitchedField <0x0008, uint8_t>,
                SwitchedField <0x0010, uint16_t>,
                SwitchedField <0x0020, float>,
                SwitchedField <0x0040, float>,
                SwitchedField <0x0080, uint16_t>,
                SwitchedField <0x0100, float>,
                SwitchedField <0x0200, float> >>
    {
        public:
            ACCESSOR_1(0,      uint8_t, Unknown1)
            ACCESSOR_1(1,      std::string, Name)
            ACCESSOR_1(2,      uint8_t, Unknown2)
            ACCESSOR_2(3, 0,   float, DamageOriginal)
            ACCESSOR_2(3, 1,   float, DamageAbsorbed)
            ACCESSOR_2(3, 2,   float, DamageActual)
            ACCESSOR_2(3, 3,   uint8_t, Unknown3)
            ACCESSOR_2(3, 4,   uint16_t, Unknown4)
            ACCESSOR_2(3, 5,   float, HealingOriginal)
            ACCESSOR_2(3, 6,   float, HealingActual)
            ACCESSOR_2(3, 7,   uint16_t, Unknown5)
            ACCESSOR_2(3, 8,   float, Unknown6)
            ACCESSOR_2(3, 9,   float, Threat)
    };

    class AreaEffEventMessageEffect : public BasicSerializable <
            BasicVector <uint32_t, AreaEffEventMessageAction>, uint64_t, uint8_t, 
            SwitchedSerializable <uint8_t,
                SwitchedField <0x01, uint8_t>,
                SwitchedField <0x02, uint64_t>,
                SwitchedField <0x04, uint8_t>,
                SwitchedField <0x10, float>,
                SwitchedField <0x20, uint8_t>,
                SwitchedField <0x08, BasicVector <uint32_t, uint8_t> >>>
    {
        public:
            ACCESSOR_1(0,      std::vector <AreaEffEventMessageAction>, Actions)
            ACCESSOR_1(1,      uint64_t, TargetID)
            ACCESSOR_1(2,      uint8_t, Unknown1)
            ACCESSOR_2(3, 0,   uint8_t, Unknown2)
            ACCESSOR_2(3, 1,   uint64_t, Unknown3)
            ACCESSOR_2(3, 2,   uint8_t, Unknown4)
            ACCESSOR_2(3, 3,   float, Unknown5)
            ACCESSOR_2(3, 4,   uint8_t, Unknown6)
            ACCESSOR_2(3, 5,   std::vector <uint8_t>, Unknown7)
    };

    class AreaEffEventMessage : public BasicSerializable <uint32_t, uint32_t, CheckedFrame <uint32_t, BasicSerializable <
            BasicVector <uint32_t, AreaEffEventMessageEffect>, uint64_t, uint64_t, uint8_t, uint8_t, uint8_t,
            SwitchedSerializable <uint8_t,
                SwitchedField <0x01, uint64_t>,
                SwitchedField <0x02, uint16_t>,
                SwitchedField <0x04, uint64_t>,
                SwitchedField <0x08, uint64_t>,
                SwitchedField <0x20, uint64_t>,
                SwitchedField <0x10, BasicArray <3, float>>>,
            Padding <0x00> >>>
    {
        public:
            using Vec3 = std::array <float, 3>; 
            ACCESSOR_1(0,         uint32_t, MessageID)
            ACCESSOR_1(1,         uint32_t, StreamID)
            ACCESSOR_2(2, 0,      std::vector <AreaEffEventMessageEffect>, Effects)
            ACCESSOR_2(2, 1,      uint64_t, SourceID)
            ACCESSOR_2(2, 2,      uint64_t, Unknown1)
            ACCESSOR_2(2, 3,      uint8_t, Unknown2)
            ACCESSOR_2(2, 4,      uint8_t, Unknown3)
            ACCESSOR_2(2, 5,      uint8_t, Unknown4)
            ACCESSOR_3(2, 6, 0,   uint64_t, Unknown5)
            ACCESSOR_3(2, 6, 1,   uint16_t, Unknown6)
            ACCESSOR_3(2, 6, 2,   uint64_t, Unknown7)
            ACCESSOR_3(2, 6, 3,   uint64_t, EffectID)
            ACCESSOR_3(2, 6, 4,   uint64_t, Unknown8)
            ACCESSOR_3(2, 6, 5,   Vec3, TargetPosition);
            ACCESSOR_2(2, 7,      uint32_t, Padding);
    };
};
