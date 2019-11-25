﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace NexusToRServer.NET.Packets.Server
{
    class CharacterListReply : TORGameServerPacket
    {
        private byte _module;
        private UInt16 _unk01, _unk02;

        public CharacterListReply(UInt16 Unk01, UInt16 Unk02)
        {
            //
            _unk01 = Unk01;
            _unk02 = Unk02;
        }

        /// <summary>
        /// Writes and Constructs the specified Packet
        /// </summary>
        public override void WriteImplementation()
        {
            // TODO: Implement this
            WriteUInt32((UInt32)GetType()); // Packet Type
            WriteUInt16(_unk02);
            WriteUInt16(_unk01);

            WriteBytes(new byte[] { 0x03, 0x00, 0x00, 0x00, 0x03, 0x82, 0x8A, 0x21, 0x0E, 0x01, 0x00, 0x40, 0xAA, 0x11, 0x75, 0x4E, 0x99, 0x08, 0x00, 0x00, 0x80, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x05, 0x00, 0x02, 0x4C, 0x01, 0x00, 0x00, 0x15, 0x15, 0xCF, 0x40, 0x00, 0x00, 0x04, 0xE0, 0xD7, 0x68, 0xB5, 0x03, 0x01, 0xCC, 0x07, 0xD8, 0x87, 0xD6, 0x02, 0x03, 0x00, 0xCC, 0x29, 0x40, 0x56, 0x77, 0x5B, 0x03, 0x01, 0xC4, 0x30, 0x1A, 0x0D, 0x75, 0xB9, 0x15, 0xCD, 0x0B, 0xCD, 0xB5, 0x4E, 0x4D, 0x03, 0xCC, 0x07, 0x18, 0xC2, 0x55, 0x7C, 0x09, 0x04, 0x04, 0xCF, 0x40, 0x00, 0x00, 0x30, 0x5C, 0x21, 0xB1, 0x10, 0x02, 0xC9, 0x03, 0xB5, 0x01, 0x02, 0xC9, 0x03, 0xB4, 0x01, 0x02, 0xC9, 0x03, 0xB3, 0x01, 0x02, 0x9F, 0xCC, 0x3C, 0x83, 0x40, 0xCC, 0xDB, 0x02, 0x00, 0xC4, 0x3B, 0xF1, 0x44, 0xC7, 0x23, 0x02, 0x0B, 0xCC, 0x27, 0x32, 0x2B, 0x0D, 0xFD, 0x02, 0xCA, 0x78, 0x18, 0xDA, 0xCB, 0x50, 0x5D, 0x6C, 0xC6, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x25, 0x42, 0x9A, 0x25, 0xBA, 0x02, 0xCF, 0x30, 0xFF, 0x93, 0x4E, 0x73, 0x16, 0xF1, 0xE7, 0xCB, 0x6C, 0x9C, 0xB1, 0xA7, 0x01, 0xCF, 0xE0, 0x00, 0x0A, 0x96, 0x0D, 0x20, 0xEC, 0xC9, 0xCC, 0x25, 0xEB, 0x85, 0x46, 0x42, 0x03, 0x00, 0xC4, 0x25, 0xD0, 0x6C, 0xA1, 0x13, 0x07, 0x01, 0x03, 0x03, 0x01, 0xCF, 0xE0, 0x00, 0x30, 0x77, 0x6C, 0xB4, 0x98, 0xBC, 0x02, 0xCF, 0xE0, 0x00, 0xA6, 0x2E, 0xD2, 0x3E, 0xB8, 0xF1, 0x03, 0xCF, 0xE0, 0x00, 0xC7, 0xA6, 0x93, 0x57, 0xD6, 0x58, 0x11, 0x02, 0xCF, 0x15, 0xD1, 0x3E, 0x19, 0xB0, 0x91, 0x72, 0x61, 0xCC, 0x02, 0xEE, 0xCD, 0xCF, 0x87, 0x08, 0x00, 0x02, 0x08, 0x08, 0xD2, 0x01, 0x31, 0xC9, 0x04, 0x8E, 0xD2, 0x01, 0x35, 0xC9, 0x04, 0xC0, 0xD2, 0x01, 0x37, 0xC9, 0x04, 0x3D, 0xD2, 0x02, 0x31, 0x30, 0xC9, 0x04, 0x0A, 0xD2, 0x02, 0x31, 0x31, 0xC9, 0x04, 0x2B, 0xD2, 0x02, 0x31, 0x32, 0xC9, 0x04, 0x60, 0xD2, 0x02, 0x31, 0x34, 0xC9, 0x04, 0x4C, 0xD2, 0x02, 0x31, 0x36, 0xC9, 0x04, 0x09, 0xCF, 0x3F, 0xFF, 0xFF, 0xF5, 0x58, 0x76, 0x5E, 0x0F, 0x01, 0xCF, 0x40, 0x00, 0x01, 0x0E, 0x21, 0x8A, 0x82, 0x04, 0x01, 0x06, 0x0A, 0x58, 0x69, 0x73, 0x74, 0x65, 0x6C, 0x6C, 0x65, 0x73, 0x73, 0x02, 0x02, 0x01, 0x03, 0x01, 0xCF, 0x40, 0x00, 0x00, 0x00, 0x51, 0xFB, 0xCA, 0xB7, 0xC7, 0x3F, 0xFF, 0xFF, 0xD2, 0xA9, 0x55, 0x93, 0x1A, 0x02, 0x01, 0x09, 0x82, 0x8A, 0x21, 0x0E, 0x01, 0x00, 0x40, 0xAA, 0x11, 0x75, 0x4E, 0x99, 0x08, 0x00, 0x00, 0x80, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x05, 0x00, 0x02, 0x4C, 0x01, 0x00, 0x00, 0x15, 0x15, 0xCF, 0x40, 0x00, 0x00, 0x04, 0xE0, 0xD7, 0x68, 0xB5, 0x03, 0x01, 0xCC, 0x07, 0xD8, 0x87, 0xD6, 0x02, 0x03, 0x00, 0xCC, 0x29, 0x40, 0x56, 0x77, 0x5B, 0x03, 0x01, 0xC4, 0x30, 0x1A, 0x0D, 0x75, 0xB9, 0x15, 0xCD, 0x0B, 0xCD, 0xB5, 0x50, 0xF1, 0x95, 0xCC, 0x07, 0x18, 0xC2, 0x55, 0x7C, 0x09, 0x04, 0x04, 0xCF, 0x40, 0x00, 0x00, 0x30, 0x5C, 0x21, 0xB1, 0x10, 0x02, 0xC9, 0x03, 0xB5, 0x01, 0x02, 0xC9, 0x03, 0xB4, 0x01, 0x02, 0xC9, 0x03, 0xB3, 0x01, 0x02, 0x9F, 0xCC, 0x3C, 0x83, 0x40, 0xCC, 0xDB, 0x02, 0x00, 0xC4, 0x3B, 0xF1, 0x44, 0xC7, 0x23, 0x02, 0x0B, 0xCC, 0x27, 0x32, 0x2B, 0x0D, 0xFD, 0x02, 0xCA, 0x78, 0x18, 0xDA, 0xCB, 0x50, 0x5D, 0x6C, 0xC6, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x25, 0x42, 0x9A, 0x25, 0xBA, 0x02, 0xCF, 0x30, 0xFF, 0x93, 0x4E, 0x73, 0x16, 0xF1, 0xE7, 0xCB, 0x6C, 0x9C, 0xB1, 0xA7, 0x01, 0xCF, 0xE0, 0x00, 0x0A, 0x96, 0x0D, 0x20, 0xEC, 0xC9, 0xCC, 0x25, 0xEB, 0x85, 0x46, 0x42, 0x03, 0x00, 0xC4, 0x25, 0xD0, 0x6C, 0xA1, 0x13, 0x07, 0x01, 0x03, 0x03, 0x01, 0xCF, 0xE0, 0x00, 0x30, 0x77, 0x6C, 0xB4, 0x98, 0xBC, 0x02, 0xCF, 0xE0, 0x00, 0xA6, 0x2E, 0xD2, 0x3E, 0xB8, 0xF1, 0x03, 0xCF, 0xE0, 0x00, 0xC7, 0xA6, 0x93, 0x57, 0xD6, 0x58, 0x11, 0x02, 0xCF, 0x15, 0xE2, 0x3B, 0x19, 0xB0, 0x9F, 0xE0, 0x7B, 0xCC, 0x02, 0xEE, 0xCD, 0xCF, 0x87, 0x08, 0x00, 0x02, 0x08, 0x08, 0xD2, 0x01, 0x31, 0xC9, 0x04, 0x76, 0xD2, 0x01, 0x35, 0xC9, 0x04, 0xAA, 0xD2, 0x01, 0x37, 0xC9, 0x04, 0x40, 0xD2, 0x02, 0x31, 0x30, 0xC9, 0x04, 0x72, 0xD2, 0x02, 0x31, 0x31, 0xC9, 0x04, 0x67, 0xD2, 0x02, 0x31, 0x32, 0xC9, 0x04, 0x44, 0xD2, 0x02, 0x31, 0x34, 0xC9, 0x04, 0x18, 0xD2, 0x02, 0x31, 0x36, 0xC9, 0x04, 0x89, 0xCF, 0x3F, 0xFF, 0xFF, 0xF5, 0x58, 0x76, 0x5E, 0x0F, 0x01, 0xCF, 0x40, 0x00, 0x01, 0x0E, 0x21, 0x8A, 0x82, 0x0A, 0x01, 0x06, 0x0A, 0x43, 0x61, 0x73, 0x73, 0x69, 0x75, 0x6D, 0x65, 0x6C, 0x6C, 0x02, 0x02, 0x01, 0x03, 0x01, 0xCF, 0x40, 0x00, 0x00, 0x00, 0x51, 0xFB, 0xCA, 0xB7, 0xC7, 0x3F, 0xFF, 0xFF, 0xD2, 0xA9, 0x55, 0x93, 0x1A, 0x02, 0x01, 0x9B, 0x83, 0x8A, 0x21, 0x0E, 0x01, 0x00, 0x40, 0xAA, 0x11, 0x75, 0x4E, 0x99, 0x08, 0x00, 0x00, 0x80, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x05, 0x00, 0x02, 0x46, 0x01, 0x00, 0x00, 0x15, 0x15, 0xCF, 0x40, 0x00, 0x00, 0x04, 0xE0, 0xD7, 0x68, 0xB5, 0x03, 0x01, 0xCC, 0x07, 0xD8, 0x87, 0xD6, 0x02, 0x03, 0x00, 0xCC, 0x29, 0x40, 0x56, 0x77, 0x5B, 0x03, 0x01, 0xC4, 0x30, 0x1A, 0x0D, 0x75, 0xB9, 0x15, 0xCD, 0x0B, 0xCD, 0xDA, 0x5E, 0x8A, 0x0A, 0xCC, 0x07, 0x18, 0xC2, 0x55, 0x7C, 0x09, 0x04, 0x04, 0xCF, 0x40, 0x00, 0x00, 0x30, 0x5C, 0x21, 0xB1, 0x10, 0x02, 0xC9, 0x02, 0xEE, 0x01, 0x02, 0xC9, 0x03, 0x12, 0x01, 0x02, 0xC9, 0x03, 0x11, 0x01, 0x02, 0x9D, 0xCC, 0x3C, 0x83, 0x40, 0xCC, 0xDB, 0x02, 0x00, 0xC4, 0x3B, 0xF1, 0x44, 0xC7, 0x23, 0x02, 0x0B, 0xCC, 0x27, 0x32, 0x2B, 0x0D, 0xFD, 0x02, 0xCA, 0x78, 0x18, 0xDA, 0xCB, 0x50, 0x5D, 0x6C, 0xC6, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x25, 0x42, 0x9A, 0x25, 0xBA, 0x02, 0xCF, 0x74, 0xF6, 0x43, 0xDB, 0xDC, 0x94, 0x0E, 0x4D, 0xCB, 0x6C, 0x9C, 0xB1, 0xA7, 0x01, 0xCF, 0xE0, 0x00, 0xC6, 0xAE, 0x44, 0xA4, 0x1E, 0x9C, 0xCC, 0x25, 0xEB, 0x85, 0x46, 0x42, 0x03, 0x00, 0xC4, 0x25, 0xD0, 0x6C, 0xA1, 0x13, 0x07, 0x01, 0x03, 0x03, 0x01, 0xCF, 0xE0, 0x00, 0x49, 0x40, 0x7A, 0xE4, 0xB9, 0x9F, 0x02, 0xCF, 0xE0, 0x00, 0x1B, 0xB1, 0xD0, 0xC0, 0x83, 0x3D, 0x03, 0xCF, 0xE0, 0x00, 0xFA, 0xD6, 0xD4, 0x10, 0x89, 0xBF, 0x11, 0x02, 0xCF, 0x15, 0xD1, 0x3B, 0x19, 0xB0, 0x91, 0x6D, 0x48, 0xCC, 0x02, 0xEE, 0xCD, 0xCF, 0x87, 0x08, 0x00, 0x02, 0x08, 0x08, 0xD2, 0x01, 0x31, 0xC9, 0x04, 0x59, 0xD2, 0x01, 0x35, 0xC9, 0x04, 0xB5, 0xD2, 0x01, 0x37, 0xC9, 0x14, 0xC2, 0xD2, 0x02, 0x31, 0x30, 0xC9, 0x04, 0x49, 0xD2, 0x02, 0x31, 0x31, 0xC9, 0x04, 0x90, 0xD2, 0x02, 0x31, 0x32, 0xC9, 0x04, 0x37, 0xD2, 0x02, 0x31, 0x34, 0xC9, 0x04, 0x4A, 0xD2, 0x02, 0x31, 0x36, 0xC9, 0x04, 0xCB, 0xCF, 0x3F, 0xFF, 0xFF, 0xF5, 0x58, 0x76, 0x5E, 0x0F, 0x01, 0xCF, 0x40, 0x00, 0x01, 0x0E, 0x21, 0x8A, 0x83, 0x9C, 0x01, 0x06, 0x04, 0x54, 0x61, 0x63, 0x69, 0x02, 0x02, 0x01, 0x03, 0x01, 0xCF, 0x40, 0x00, 0x00, 0x00, 0x55, 0xF4, 0xC6, 0x11, 0xC7, 0x3F, 0xFF, 0xFF, 0xD2, 0xA9, 0x55, 0x93, 0x1A, 0x02, 0x01, 0x72, 0xB7, 0x91, 0x2D, 0x0D, 0x01, 0x00, 0x40, 0xAA, 0xE1, 0x3A, 0x4E, 0x3A, 0x35, 0x00, 0x00, 0x40, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x52, 0x44, 0xF4, 0xCB, 0x0C, 0x01, 0x00, 0x40, 0x05, 0x00, 0x02, 0x4A, 0x00, 0x00, 0x00, 0x04, 0x04, 0xCF, 0x40, 0x00, 0x00, 0x35, 0xF7, 0x0E, 0xB2, 0x11, 0x08, 0x00, 0x09, 0x01, 0x01, 0xD2, 0x13, 0x34, 0x36, 0x31, 0x31, 0x36, 0x38, 0x37, 0x31, 0x37, 0x38, 0x36, 0x33, 0x31, 0x32, 0x38, 0x33, 0x36, 0x31, 0x32, 0x03, 0x03, 0xCF, 0x40, 0x00, 0x00, 0x35, 0xF7, 0x0E, 0xB2, 0x0F, 0x01, 0x00, 0x01, 0x05, 0x01, 0xCC, 0x13, 0x71, 0x2C, 0x30, 0x40, 0x02, 0x00, 0xC3, 0xBC, 0xC0, 0x77, 0x2F, 0x06, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0x12, 0x00, 0x32, 0x00, 0x2D, 0x06, 0x00, 0x00, 0x3C, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3E, 0x3C, 0x75, 0x73, 0x65, 0x72, 0x64, 0x61, 0x74, 0x61, 0x3E, 0x3C, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x33, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x49, 0x64, 0x3D, 0x22, 0x35, 0x33, 0x39, 0x30, 0x34, 0x33, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x31, 0x33, 0x31, 0x31, 0x38, 0x34, 0x30, 0x33, 0x39, 0x32, 0x38, 0x33, 0x36, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x6F, 0x6E, 0x73, 0x75, 0x6D, 0x65, 0x64, 0x20, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x73, 0x74, 0x61, 0x72, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x45, 0x61, 0x72, 0x6C, 0x79, 0x20, 0x41, 0x63, 0x63, 0x65, 0x73, 0x73, 0x22, 0x20, 0x20, 0x20, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x49, 0x6E, 0x66, 0x6F, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x61, 0x72, 0x64, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x68, 0x65, 0x32, 0x30, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x65, 0x79, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x74, 0x79, 0x70, 0x65, 0x3D, 0x22, 0x47, 0x22, 0x2F, 0x3E, 0x3C, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x33, 0x39, 0x22, 0x20, 0x20, 0x20, 0x20, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x49, 0x64, 0x3D, 0x22, 0x31, 0x35, 0x31, 0x33, 0x30, 0x35, 0x39, 0x33, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x31, 0x33, 0x32, 0x33, 0x38, 0x37, 0x31, 0x32, 0x33, 0x37, 0x30, 0x30, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x6F, 0x6E, 0x73, 0x75, 0x6D, 0x65, 0x64, 0x20, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x73, 0x74, 0x61, 0x72, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x48, 0x65, 0x61, 0x64, 0x20, 0x53, 0x74, 0x61, 0x72, 0x74, 0x22, 0x20, 0x20, 0x20, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x49, 0x6E, 0x66, 0x6F, 0x3D, 0x22, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x20, 0x62, 0x79, 0x20, 0x48, 0x65, 0x61, 0x64, 0x20, 0x53, 0x74, 0x61, 0x72, 0x74, 0x20, 0x50, 0x61, 0x63, 0x6B, 0x61, 0x67, 0x65, 0x22, 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x61, 0x72, 0x64, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x68, 0x65, 0x32, 0x30, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x65, 0x79, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x74, 0x79, 0x70, 0x65, 0x3D, 0x22, 0x47, 0x22, 0x2F, 0x3E, 0x3C, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x32, 0x30, 0x31, 0x33, 0x22, 0x20, 0x20, 0x20, 0x20, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x49, 0x64, 0x3D, 0x22, 0x31, 0x39, 0x36, 0x36, 0x39, 0x34, 0x32, 0x34, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x31, 0x33, 0x32, 0x34, 0x33, 0x37, 0x31, 0x31, 0x31, 0x33, 0x39, 0x30, 0x37, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x6F, 0x6E, 0x73, 0x75, 0x6D, 0x65, 0x64, 0x20, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x73, 0x74, 0x61, 0x72, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x53, 0x57, 0x54, 0x4F, 0x52, 0x5F, 0x43, 0x4F, 0x4C, 0x4C, 0x45, 0x43, 0x54, 0x4F, 0x52, 0x53, 0x5F, 0x52, 0x45, 0x54, 0x41, 0x49, 0x4C, 0x22, 0x20, 0x20, 0x20, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x49, 0x6E, 0x66, 0x6F, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x61, 0x72, 0x64, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x68, 0x65, 0x32, 0x30, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x65, 0x79, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x74, 0x79, 0x70, 0x65, 0x3D, 0x22, 0x47, 0x22, 0x2F, 0x3E, 0x3C, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x49, 0x64, 0x3D, 0x22, 0x32, 0x32, 0x37, 0x36, 0x35, 0x33, 0x38, 0x35, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x31, 0x33, 0x32, 0x34, 0x35, 0x39, 0x33, 0x39, 0x37, 0x31, 0x31, 0x33, 0x39, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x6F, 0x6E, 0x73, 0x75, 0x6D, 0x65, 0x64, 0x20, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x73, 0x74, 0x61, 0x72, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x53, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79, 0x20, 0x4B, 0x65, 0x79, 0x20, 0x41, 0x73, 0x73, 0x6F, 0x63, 0x69, 0x61, 0x74, 0x65, 0x64, 0x22, 0x20, 0x20, 0x20, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x49, 0x6E, 0x66, 0x6F, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x61, 0x72, 0x64, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x68, 0x65, 0x32, 0x30, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x65, 0x79, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x74, 0x79, 0x70, 0x65, 0x3D, 0x22, 0x47, 0x22, 0x2F, 0x3E, 0x3C, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x37, 0x31, 0x22, 0x20, 0x20, 0x20, 0x20, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x49, 0x64, 0x3D, 0x22, 0x32, 0x39, 0x32, 0x37, 0x37, 0x35, 0x37, 0x31, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x31, 0x33, 0x32, 0x37, 0x33, 0x34, 0x38, 0x33, 0x30, 0x32, 0x37, 0x38, 0x34, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x6F, 0x6E, 0x73, 0x75, 0x6D, 0x65, 0x64, 0x20, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x73, 0x74, 0x61, 0x72, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x45, 0x61, 0x72, 0x6C, 0x79, 0x20, 0x46, 0x6F, 0x75, 0x6E, 0x64, 0x65, 0x72, 0x22, 0x20, 0x20, 0x20, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x49, 0x6E, 0x66, 0x6F, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x61, 0x72, 0x64, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x68, 0x65, 0x32, 0x30, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x65, 0x79, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x74, 0x79, 0x70, 0x65, 0x3D, 0x22, 0x47, 0x22, 0x2F, 0x3E, 0x3C, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x38, 0x37, 0x22, 0x20, 0x20, 0x20, 0x20, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x49, 0x64, 0x3D, 0x22, 0x33, 0x33, 0x31, 0x36, 0x39, 0x30, 0x37, 0x33, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x31, 0x33, 0x32, 0x39, 0x38, 0x39, 0x39, 0x34, 0x32, 0x39, 0x30, 0x30, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x6F, 0x6E, 0x73, 0x75, 0x6D, 0x65, 0x64, 0x20, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x73, 0x74, 0x61, 0x72, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x42, 0x75, 0x64, 0x64, 0x79, 0x20, 0x74, 0x72, 0x69, 0x61, 0x6C, 0x20, 0x2D, 0x20, 0x45, 0x6C, 0x69, 0x67, 0x69, 0x62, 0x6C, 0x65, 0x20, 0x74, 0x6F, 0x20, 0x53, 0x65, 0x6E, 0x64, 0x20, 0x54, 0x72, 0x69, 0x61, 0x6C, 0x20, 0x52, 0x65, 0x66, 0x65, 0x72, 0x72, 0x61, 0x6C, 0x22, 0x20, 0x20, 0x20, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x49, 0x6E, 0x66, 0x6F, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x61, 0x72, 0x64, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x68, 0x65, 0x32, 0x30, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x65, 0x79, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x74, 0x79, 0x70, 0x65, 0x3D, 0x22, 0x47, 0x22, 0x2F, 0x3E, 0x3C, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x37, 0x22, 0x20, 0x20, 0x20, 0x20, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x49, 0x64, 0x3D, 0x22, 0x33, 0x37, 0x34, 0x31, 0x36, 0x39, 0x34, 0x33, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x31, 0x33, 0x33, 0x32, 0x32, 0x38, 0x39, 0x39, 0x31, 0x31, 0x30, 0x38, 0x39, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x63, 0x6F, 0x6E, 0x73, 0x75, 0x6D, 0x65, 0x64, 0x20, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x61, 0x74, 0x65, 0x5F, 0x73, 0x74, 0x61, 0x72, 0x74, 0x65, 0x64, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x53, 0x75, 0x62, 0x73, 0x63, 0x72, 0x69, 0x62, 0x65, 0x72, 0x20, 0x53, 0x68, 0x61, 0x72, 0x64, 0x20, 0x41, 0x63, 0x63, 0x65, 0x73, 0x73, 0x22, 0x20, 0x20, 0x20, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x49, 0x6E, 0x66, 0x6F, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x61, 0x72, 0x64, 0x5F, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x68, 0x65, 0x32, 0x30, 0x34, 0x30, 0x22, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x65, 0x79, 0x3D, 0x22, 0x22, 0x20, 0x20, 0x20, 0x20, 0x74, 0x79, 0x70, 0x65, 0x3D, 0x22, 0x47, 0x22, 0x2F, 0x3E, 0x3C, 0x2F, 0x75, 0x73, 0x65, 0x72, 0x64, 0x61, 0x74, 0x61, 0x3E, 0x3C, 0x2F, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
        

            /*WriteByte(0x00);
            WriteUInt64(0x00);
            WriteUInt32(0x00);
            WriteUInt16(0x03);
            WriteUInt16(0x32);
            WriteString("<status><userdata></userdata></status>");
            WriteUInt64(0x00);*/
        }

        /// <summary>
        /// Returns the PacketType of the specified Packet
        /// </summary>
        /// <returns>PacketType of specified Packet</returns>
        public override PacketType GetType()
        {
            return PacketType.CharacterListReply;
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