#pragma once

#include "base_gom_update.h"

namespace swtorMeters
{
    class AreaAwarenessEntered : public BasicSerializable <uint32_t, uint32_t, GomUpdate>
    {
        public:
            ACCESSOR_1(0, uint32_t, MessageID)
            ACCESSOR_1(1, uint32_t, StreamID)
            ACCESSOR_1(2, GomUpdate, GomUpdate)
    };
};