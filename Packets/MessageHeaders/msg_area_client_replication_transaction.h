#pragma once

#include "base_gom_update.h"

namespace swtorMeters
{
    using Serialization::BasicSerializable;
    using Serialization::BasicVector;

    class AreaClientReplicationTransaction : public BasicSerializable <uint32_t, uint32_t, uint32_t, GomUpdate>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, uint32_t, Unknown)
            ACCESSOR_1(3, GomUpdate, GomUpdate)
    };
};
