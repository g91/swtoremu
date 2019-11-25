#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/switched_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::SwitchedSerializable;
    using Serialization::BasicSerializable;
    using Serialization::BasicContainer;
    using Serialization::BasicVector;
    using Serialization::SwitchedField;
    using Serialization::CheckedVector;
    using Serialization::Packed;

    class GomUpdateObject : public BasicSerializable <Packed <uint64_t>,
            SwitchedSerializable <uint8_t,
                SwitchedField <0x80, Packed <uint64_t>>,
                SwitchedField <0x40, Packed <uint64_t>>,
                SwitchedField <0x20, Packed <uint64_t>>,
                SwitchedField <0x10, SwitchedSerializable <uint8_t, 
                    SwitchedField <0x01, BasicVector <uint32_t, uint64_t>>,
                    SwitchedField <0x02, BasicVector <uint32_t, uint64_t>> >>,
                SwitchedField <0x08, BasicSerializable <
                    Packed <uint64_t>, Packed <uint64_t>,
                    BasicVector <Packed <uint64_t>, uint8_t> >> >> 
    {
        public:
            ACCESSOR_1(0,         uint64_t, NodeID)
            ACCESSOR_2(1, 0,      uint64_t, ClassID)
            ACCESSOR_2(1, 1,      uint64_t, TemplateID)
            ACCESSOR_2(1, 2,      uint64_t, ParentNodeID)
            ACCESSOR_3(1, 3, 0,   std::vector <uint64_t>, UnknownList1)
            ACCESSOR_3(1, 3, 1,   std::vector <uint64_t>, UnknownList2)
            ACCESSOR_3(1, 4, 0,   uint64_t, FieldVersion)
            ACCESSOR_3(1, 4, 1,   uint64_t, FieldFormat)
            ACCESSOR_3(1, 4, 2,   std::vector <uint8_t>, FieldData)
    };

    class StreamContractField : public BasicSerializable <
            Packed <uint64_t>, Packed <uint64_t>, Packed <uint64_t>>
    {
        public:
            ACCESSOR_1(0, uint64_t, Type)
            ACCESSOR_1(1, uint64_t, ClassID)
            ACCESSOR_1(2, uint64_t, ContractID)
    };

    class StreamContract : public BasicSerializable <Packed <uint64_t>, Packed <uint64_t>,
            BasicVector <Packed <uint64_t>, Packed <uint64_t>>,
            BasicVector <Packed <uint64_t>, BasicSerializable <Packed <uint64_t>, BasicVector <Packed <uint64_t>, StreamContractField>>> >
    {
        public:
            using field_vector = std::vector <BasicSerializable <Packed <uint64_t>, BasicVector <Packed <uint64_t>, StreamContractField>>>;
            ACCESSOR_1(0, uint64_t, ContractID)
            ACCESSOR_1(1, uint64_t, BaseClassID)
            ACCESSOR_1(2, std::vector <uint64_t>, GlommedClasses)
            ACCESSOR_1(3, field_vector, Fields)
    };

    class GomUpdate : public BasicSerializable <
            CheckedVector <uint32_t, Packed <uint64_t>, StreamContract>,
            SwitchedSerializable <uint8_t, 
                SwitchedField <0x01, BasicVector <Packed <uint64_t>, GomUpdateObject>>,
                SwitchedField <0x02, BasicVector <Packed <uint64_t>, Packed <uint64_t>>> >>
    {
        public:
            ACCESSOR_1(0,      std::vector <StreamContract>, ContractUpdates)
            ACCESSOR_2(1, 0,   std::vector <GomUpdateObject>, ObjectUpdates)
            ACCESSOR_2(1, 1,   std::vector <uint64_t>, UnknownList)
    };
};
