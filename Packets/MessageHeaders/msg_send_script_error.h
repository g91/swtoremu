#pragma once

#include <cstdint>

#include "../serialization/common_macros.h"
#include "../serialization/basic_serializable.h"
#include "../serialization/container_types.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicContainer;

    class SendScriptError : public BasicSerializable <uint32_t, uint32_t,
            BasicContainer <uint32_t, std::string>,
            BasicContainer <uint32_t, std::string>,
            uint64_t, uint64_t>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, std::string, ErrorMessage)
            ACCESSOR_1(3, std::string, CallTrace)
            ACCESSOR_1(4, uint64_t, CharacterID)
            ACCESSOR_1(5, uint64_t, AreaID)
    };
};

