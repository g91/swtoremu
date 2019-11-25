#pragma once

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicVector;
    using Serialization::BasicContainer;

    class AreaTalk : public BasicSerializable <uint32_t, uint32_t, 
            BasicContainer <uint32_t, std::string>, 
            BasicContainer <uint32_t, std::string> >
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, std::string, Type)
            ACCESSOR_1(3, std::string, Message)
    };
};