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
    using Serialization::BasicContainer;
    using Serialization::BasicVector;
    using Serialization::AssertGreaterOrEqual;

    class MessageTextDetail : public BasicSerializable <uint64_t, 
            SwitchedSerializable <uint8_t,
                SwitchedField <0x80, uint64_t>,
                SwitchedField <0x40, uint64_t>,
                SwitchedField <0x20, BasicSerializable <uint64_t, uint64_t>>,
                SwitchedField <0x10, SwitchedSerializable <uint8_t,
                    SwitchedField <0x01, BasicVector <uint32_t, uint64_t>>,
                    SwitchedField <0x02, BasicVector <uint32_t, uint64_t>> >>,
                SwitchedField <0x08, BasicSerializable <
                    AssertGreaterOrEqual <uint16_t, 5>, uint8_t,
                    BasicVector <uint32_t, uint8_t>>> >>
    {
        ACCESSOR_1(0,         uint64_t, NodeID)
        ACCESSOR_2(1, 0,      uint64_t, ClassID)
        ACCESSOR_2(1, 1,      uint64_t, TemplateID)
        ACCESSOR_3(1, 2, 0,   uint64_t, ParentNodeID)
        ACCESSOR_3(1, 2, 1,   uint64_t, Unknown)
        ACCESSOR_3(1, 3, 0,   std::vector <uint64_t>, Unknown1)
        ACCESSOR_3(1, 3, 1,   std::vector <uint64_t>, Unknown2)
        ACCESSOR_3(1, 4, 0,   uint16_t, Unknown3)
        ACCESSOR_3(1, 4, 1,   uint8_t, Unknown4)
        ACCESSOR_3(1, 4, 2,   std::vector <uint8_t>, Unknown5)
    };

    class MessageText : public BasicSerializable <uint32_t, uint32_t, uint64_t,
            BasicContainer <uint32_t, std::string>,
            BasicVector <uint32_t, MessageTextDetail>, uint64_t>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, uint64_t, Unknown1)
            ACCESSOR_1(3, std::string, Unknown2)
            ACCESSOR_1(4, std::vector <MessageTextDetail>, Objects)
            ACCESSOR_1(5, uint64_t, Unknown3)
    };
};

