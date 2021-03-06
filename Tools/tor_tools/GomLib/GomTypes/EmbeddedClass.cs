﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GomLib.GomTypes
{
    public class EmbeddedClass : GomType
    {
        public EmbeddedClass() : base(GomTypeId.EmbeddedClass) { }

        public ulong DomClassId { get; internal set; }
        public DomClass DomClass { get; internal set; }

        internal override void Link()
        {
            DomClass = DataObjectModel.Get<DomClass>(DomClassId);
        }

        public override string ToString()
        {
            return System.String.Format("class {0}", this.DomClass);
        }

        public override object ReadData(GomBinaryReader reader)
        {
            var obj = ScriptObjectReader.ReadObject(this.DomClass, reader);
            return obj;
        }
    }
}
