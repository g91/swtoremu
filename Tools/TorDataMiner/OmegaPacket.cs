using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Text;

namespace TorDataMiner
{
    public class PacketList : ObservableCollection<OmegaPacket> { }

    public class OmegaPacket
    {
        public UInt32 Type { get; set; }
        public Byte Module { get; set; }
        public UInt32 ID { get; set; }
        public byte[] Buffer { get; set; }

        private BinaryReader _reader;
        private MemoryStream _stream;
        private string _packetway;

        public OmegaPacket(UInt32 pType, Byte pModule, UInt32 pID, byte[] pBuffer, bool FromServer)
        {
            this.Type = pType;
            this.Module = pModule;
            this.ID = pID;
            this.Buffer = pBuffer;

            _stream = new MemoryStream(this.Buffer);
            _reader = new BinaryReader(_stream);

            _packetway = "C => S";
            if (FromServer)
                _packetway = "S => C";
        }

        public override string ToString()
        {
            return String.Format("{0} [0x{1:X8}] (0x{2:X2})", _packetway, this.Type, this.Module);
        }

        public Int16 ReadInt16()
        {
            return _reader.ReadInt16();
        }

        public Int32 ReadInt32()
        {
            return _reader.ReadInt32();
        }

        public Int64 ReadInt64()
        {
            return _reader.ReadInt64();
        }

        public UInt16 ReadUInt16()
        {
            return _reader.ReadUInt16();
        }

        public UInt32 ReadUInt32()
        {
            return _reader.ReadUInt32();
        }

        public UInt64 ReadUInt64()
        {
            return _reader.ReadUInt64();
        }

        public byte ReadByte()
        {
            return _reader.ReadByte();
        }

        public Boolean ReadBoolean()
        {
            return _reader.ReadBoolean();
        }

        public String ReadString()
        {
            UInt32 pLength = _reader.ReadUInt32();
            byte[] sData = _reader.ReadBytes((int)pLength);

            if (sData[sData.Length - 1] == 0x00)
                pLength--;

            return Encoding.ASCII.GetString(sData, 0, (int)pLength);
        }

        public byte[] ReadBytes(int count)
        {
            return _reader.ReadBytes(count);
        }

        public float ReadFloat()
        {
            return _reader.ReadSingle();
        }
    }
}
