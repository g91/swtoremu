﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace NexusToRServer.NET.Packets.Server
{
    class AreaAwarenessEntered : TORGameServerPacket
    {
        private byte _module;
        private byte[] _aww;

        public AreaAwarenessEntered(String Area, String AreaID, String AreaCode, int AwarenessID)
        {
            //
            _aww = AreaServer.Awareness.Get(Area, AreaID, AreaCode, AwarenessID);
        }

        /// <summary>
        /// Writes and Constructs the specified Packet
        /// </summary>
        public override void WriteImplementation()
        {
            WriteUInt32((UInt32)GetType()); // Packet Type
            WriteUInt32(0x00040000); // Packet Component

            WriteBytes(_aww);
        }

        /// <summary>
        /// Returns the PacketType of the specified Packet
        /// </summary>
        /// <returns>PacketType of specified Packet</returns>
        public override PacketType GetType()
        {
            return PacketType.AreaAwarenessEntered;
        }

        public override void SetModule(byte inMod)
        {
            _module = inMod;
        }

        public override byte GetModule()
        {
            return _module;
        }
    }
}
