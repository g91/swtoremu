﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GomLib.Models
{
    public enum ItemBindingRule
    {
        None = 0,
        Never = 1,
        Equip = 2,
        Pickup = 3
    }

    public static class ItemBindingRuleExtensions
    {
        public static ItemBindingRule ToBindingRule(this ScriptEnum val)
        {
            if (val == null) { return ToBindingRule(String.Empty); }
            return ToBindingRule(val.ToString());
        }

        public static ItemBindingRule ToBindingRule(this string str)
        {
            if (String.IsNullOrEmpty(str)) return ItemBindingRule.None;

            switch (str)
            {
                case "itmBindNever": return ItemBindingRule.Never;
                case "itmBindOnEquip": return ItemBindingRule.Equip;
                case "itmBindOnPickup": return ItemBindingRule.Pickup;
                case "itmBindOnLegacy": return ItemBindingRule.Pickup;
                default: throw new InvalidOperationException("Unknown BindingRule: " + str);
            }
        }
    }
}
