﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TorLib
{
    public static class Icons
    {
        public static HashSet<string> Filenames { get; set; }
        public static HashSet<string> Portraits { get; set; }
        public static HashSet<string> Codex { get; set; }
        public static Dictionary<ulong, HashSet<string>> AreaMaps { get; set; }

        static Icons()
        {
            Filenames = new HashSet<string>();
            Portraits = new HashSet<string>();
            Codex = new HashSet<string>();
            AreaMaps = new Dictionary<ulong, HashSet<string>>();
        }

        public static void Add(string filename)
        {
            if (!String.IsNullOrEmpty(filename))
            {
                Filenames.Add(filename.ToLower());
            }
        }

        public static void AddPortrait(string path)
        {
            if (!String.IsNullOrEmpty(path))
            {
                Portraits.Add(path.ToLower());
            }
        }

        public static void AddCodex(string fileName)
        {
            if (!String.IsNullOrEmpty(fileName))
            {
                Codex.Add(fileName.ToLower());
            }
        }

        public static void AddMap(ulong areaId, string mapName)
        {
            HashSet<string> set;
            if (!AreaMaps.TryGetValue(areaId, out set))
            {
                set = new HashSet<string>();
                AreaMaps[areaId] = set;
            }

            set.Add(mapName.ToLower());
        }

        public static void SaveTo(string dir, bool overwrite = false)
        {
            SaveSetTo(dir, Filenames, "/resources/gfx/icons/{0}.dds", "icon", overwrite);
        }

        public static void SavePortraitsTo(string dir, bool overwrite = false)
        {
            HashSet<string> existingFiles = new HashSet<string>();
            System.IO.FileMode fileMode = System.IO.FileMode.Create;
            if (!overwrite)
            {
                fileMode = System.IO.FileMode.CreateNew;
                string[] currentFiles = System.IO.Directory.GetFiles(dir, "*.dds");
                foreach (var fileName in currentFiles)
                {
                    existingFiles.Add(System.IO.Path.GetFileNameWithoutExtension(fileName));
                }
            }

            byte[] copyBuffer = new byte[4096];
            int filesSaved = 0;
            Portraits.ForEach(iconName =>
            {
                var portraitFileName = System.IO.Path.GetFileNameWithoutExtension(iconName);
                if (existingFiles.Contains(portraitFileName)) { return; }

                string iconPath = String.Format("/resources{0}", iconName);
                var file = Assets.FindFile(iconPath);
                if (file == null)
                {
                    Console.WriteLine("Unable to find portrait: {0}", iconPath);
                    return;
                }

                string outPath = System.IO.Path.Combine(dir, portraitFileName + ".dds");
                using (var inFile = file.Open())
                using (var outFile = System.IO.File.Open(outPath, fileMode, System.IO.FileAccess.Write))
                {
                    inFile.CopyTo(outFile, copyBuffer);
                    filesSaved++;
                }
            });

            Console.WriteLine("Saving {0} Portraits to {1} [Overwrite = {2}]", filesSaved, dir, overwrite);
        }

        public static void SaveCodexTo(string dir, bool overwrite = false)
        {
            SaveSetTo(dir, Codex, "/resources/gfx/codex/{0}.dds", "codex", overwrite);
        }

        public static void SaveMapsTo(string dir, bool overwrite = false)
        {
            foreach (var maps in AreaMaps)
            {
                var outDir = System.IO.Path.Combine(dir, maps.Key.ToString());
                if (!System.IO.Directory.Exists(outDir))
                {
                    System.IO.Directory.CreateDirectory(outDir);
                }

                SaveSetTo(outDir, maps.Value, String.Format("/resources/world/areas/{0}/{{0}}_r.dds", maps.Key), "map", overwrite);
            }
        }

        public static void ConvertDDSToJPG()
        {
            string ExecutableFilePath = System.IO.Path.Combine(System.IO.Directory.GetCurrentDirectory(), @"convertddstojpg.bat");
            string Arguments = @"";
            if (System.IO.File.Exists(ExecutableFilePath)) {
                Console.WriteLine("Executing convertddstojpg.bat : Before");
                System.Diagnostics.Process p = new System.Diagnostics.Process() { StartInfo = new System.Diagnostics.ProcessStartInfo(ExecutableFilePath, Arguments), };
                p.ErrorDataReceived += p_ErrorDataReceived;
                p.OutputDataReceived += p_OutputDataReceived;
                p.Exited += p_Exited;
                p.Start();
                Console.WriteLine("Executing convertddstojpg.bat : Executed");
            }
        }

        static void p_Exited(object sender, EventArgs e) { Console.WriteLine("Executing convertddstojpg.bat : Completed"); DeleteDDSFiles(); }
        static void p_ErrorDataReceived(object sender, System.Diagnostics.DataReceivedEventArgs e) { Console.WriteLine(e.Data); }
        static void p_OutputDataReceived(object sender, System.Diagnostics.DataReceivedEventArgs e) { Console.WriteLine(e.Data); }

        static void DeleteDDSFiles()
        {
            string[] fileList = System.IO.Directory.GetFiles(System.IO.Path.Combine(System.IO.Directory.GetCurrentDirectory(), @"images\"));
            if (fileList.Where(i => i.EndsWith(".jpg")).Count() < 1) {
                Console.WriteLine("Images were not converted to JPG, not deleting original DDS files");
                return;
            }
            for (int i = 0; i < fileList.Length; i++)
            {
                int attempt = 0;
                while (attempt < 3 && System.IO.File.Exists(fileList[i]))
                {
                    System.IO.File.Delete(fileList[i]);
                    attempt++;
                }
            }
            Console.WriteLine("Images were not converted to JPG, not deleting original DDS files");
        }

        private static void SaveSetTo(string dir, HashSet<string> fileNames, string internalPathFormat, string imageType, bool overwrite)
        {
            HashSet<string> existingFiles = new HashSet<string>();
            System.IO.FileMode fileMode = System.IO.FileMode.Create;
            if (!overwrite)
            {
                fileMode = System.IO.FileMode.CreateNew;
                string[] currentFiles = System.IO.Directory.GetFiles(dir, "*.dds");
                foreach (var fileName in currentFiles)
                {
                    existingFiles.Add(System.IO.Path.GetFileNameWithoutExtension(fileName));
                }
            }

            byte[] copyBuffer = new byte[4096];
            int filesSaved = 0;
            fileNames.ForEach(iconName =>
            {
                var fileName = iconName;
                if (existingFiles.Contains(iconName)) { return; }

                string iconPath = String.Format(internalPathFormat, iconName);
                var file = Assets.FindFile(iconPath);
                if (file == null)
                {
                    Console.WriteLine("Unable to find {1}: {0}", iconPath, imageType);
                    return;
                }

                string outPath = System.IO.Path.Combine(dir, iconName + ".dds");
                using (var inFile = file.Open())
                using (var outFile = System.IO.File.Open(outPath, fileMode, System.IO.FileAccess.Write))
                {
                    inFile.CopyTo(outFile, copyBuffer);
                    filesSaved++;
                }
            });

            Console.WriteLine("Saving {0} {3} Images to {1} [Overwrite = {2}]", filesSaved, dir, overwrite, imageType);
        }
    }
}
