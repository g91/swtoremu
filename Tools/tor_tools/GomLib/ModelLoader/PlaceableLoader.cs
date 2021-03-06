﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GomLib.Models;

namespace GomLib.ModelLoader
{
    public class PlaceableLoader
    {
        const long NameLookupKey = -2761358831308646330;

        static Dictionary<ulong, Placeable> idMap = new Dictionary<ulong, Placeable>();
        static Dictionary<string, Placeable> nameMap = new Dictionary<string, Placeable>();

        public string ClassName
        {
            get { return "plcTemplate"; }
        }

        public static Placeable Load(ulong nodeId)
        {
            Placeable result;
            if (idMap.TryGetValue(nodeId, out result))
            {
                return result;
            }

            GomObject obj = DataObjectModel.GetObject(nodeId);
            Placeable plc = new Placeable();
            return Load(plc, obj);
        }

        public static Models.Placeable Load(string fqn)
        {
            Placeable result;
            if (nameMap.TryGetValue(fqn, out result))
            {
                return result;
            }

            GomObject obj = DataObjectModel.GetObject(fqn);
            Placeable plc = new Placeable();
            return Load(plc, obj);
        }

        public static Models.Placeable Load(Models.Placeable plc, GomObject obj)
        {
            if (obj == null) { return null; }
            if (plc == null) { return null; }

            plc.Fqn = obj.Name;
            plc.NodeId = obj.Id;

            var textLookup = obj.Data.Get<Dictionary<object,object>>("locTextRetrieverMap");
            var nameLookupData = (GomObjectData)textLookup[NameLookupKey];
            long nameId = nameLookupData.Get<long>("strLocalizedTextRetrieverStringID");
            plc.Id = (ulong)(nameId >> 32);
            plc.Name = StringTable.TryGetString(plc.Fqn, nameLookupData);

            //public Conversation Conversation { get; set; }
            string cnvFqn = obj.Data.ValueOrDefault<string>("plcConvo", null);
            // if (cnvFqn != null) { plc.Conversation = ConversationLoader.Load(cnvFqn); }

            //public Codex Codex { get; set; }
            ulong cdxNodeId = obj.Data.ValueOrDefault<ulong>("plcCodexSpec", 0);
            if (cdxNodeId > 0) { plc.Codex = CodexLoader.Load(cdxNodeId); }

            //public Profession RequiredProfession { get; set; }
            plc.RequiredProfession = ProfessionExtensions.ToProfession((ScriptEnum)obj.Data.ValueOrDefault<ScriptEnum>("prfProfessionRequired", null));

            //public int RequiredProfessionLevel { get; set; }
            plc.RequiredProfessionLevel = (int)obj.Data.ValueOrDefault<long>("prfProfessionLevelRequired", 0);

            //public bool IsBank { get; set; }
            plc.IsBank = obj.Data.ValueOrDefault<bool>("field_400000070210234D", false);

            //public bool IsMailbox { get; set; }
            plc.IsMailbox = obj.Data.ValueOrDefault<bool>("plcIsMailbox", false);

            //public AuctionHouseNetwork AuctionNetwork { get; set; }
            plc.AuctionNetwork = AuctionHouseNetworkExtensions.ToAuctionHouseNetwork((ScriptEnum)obj.Data.ValueOrDefault<ScriptEnum>("field_40000008D92E8668", null));

            //public bool IsAuctionHouse { get; set; }
            plc.IsAuctionHouse = plc.AuctionNetwork != AuctionHouseNetwork.None;

            //public bool IsEnhancementStation { get; set; }
            plc.IsEnhancementStation = EnhancementStationType.None != EnhancementStationTypeExtensions.ToEnhancementStationType((ScriptEnum)obj.Data.ValueOrDefault<ScriptEnum>("itmEnhancementStationType", null));

            //public Faction Faction { get; set; }
            plc.Faction = FactionExtensions.ToFaction(obj.Data.ValueOrDefault<long>("plcFaction", 0));

            //public int LootLevel { get; set; }
            plc.LootLevel = (int)obj.Data.ValueOrDefault<long>("plcdynLootLevel", 0);

            //public long LootPackageId { get; set; }
            plc.LootPackageId = obj.Data.ValueOrDefault<long>("plcdynLootPackage", 0);

            //public long WonkaPackageId { get; set; }
            plc.WonkaPackageId = obj.Data.ValueOrDefault<long>("wnkPackageID", 0);

            //public DifficultyLevel Difficulty { get; set; }
            plc.DifficultyFlags = (int)obj.Data.ValueOrDefault<long>("spnDifficultyLevelFlags", 0);

            //public HydraScript HydraScript { get; set; }
            ulong hydNodeId = obj.Data.ValueOrDefault<ulong>("field_4000000A4FA14A25", 0);
            if (hydNodeId > 0)
            {
                //plc.HydraScript = HydraScriptLoader.Load(hydNodeId);
            }

            Categorize(plc, obj);

            return plc;
        }

        private static void Categorize(Placeable plc, GomObject obj)
        {
            if (plc.IsMailbox) { plc.Category = PlaceableCategory.Mailbox; return; }
            if (plc.IsBank) { plc.Category = PlaceableCategory.Bank; return; }
            if (plc.IsAuctionHouse) { plc.Category = PlaceableCategory.AuctionHouse; return; }
            if (plc.IsEnhancementStation) { plc.Category = PlaceableCategory.EnhancementStation; return; }
            if (plc.Fqn.Contains("juke")) { plc.Category = PlaceableCategory.Jukebox; return; }

            // All Gathering Resource Nodes are in 'plc.generic.harvesting'
            if (plc.Fqn.StartsWith("plc.generic.harvesting."))
            {
                plc.Category = PlaceableCategory.ResourceNode;
                return;
            }

            if (obj.Data.ValueOrDefault<ulong>("plcAbilitySpecOnUse", 0) == 16140902321107152398)
            {
                plc.Category = PlaceableCategory.Bindpoint;
                return;
            }

            if (plc.LootPackageId != 0) { plc.Category = PlaceableCategory.TreasureChest; return; }
            if (plc.Fqn.Contains("data_holocron")) { plc.Category = PlaceableCategory.Holocron; return; }
            if (obj.Data.ContainsKey("plcTaxiTerminalSpec")) { plc.Category = PlaceableCategory.TaxiTerminal; return; }

            if (plc.Codex != null) { plc.Category = PlaceableCategory.Codex; return; }
            if (plc.WonkaPackageId != 0) { plc.Category = PlaceableCategory.Elevator; return; }

            if (plc.Fqn.StartsWith("plc.location.")) { plc.Category = PlaceableCategory.Quest; }
        }

        public void LoadObject(Models.GameObject loadMe, GomObject obj)
        {
            GomLib.Models.Placeable loadObj = (Models.Placeable)loadMe;
            Load(loadObj, obj);
        }

        public void LoadReferences(Models.GameObject obj, GomObject gom)
        {
            // No references to load
        }
    }
}
