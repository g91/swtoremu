using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using System.Windows.Media.Imaging;
using System.Windows;
using Microsoft.Win32;

namespace NexusLauncher
{
    public class Game
    {
        public string Title { get; set; }
        public string Identifier { get; set; }
        public string Description { get; set; }
        public string Location { get; set; }
        public string CheckEXE { get; set; }
        public string Executable { get; set; }
        public string Arguments { get; set; }
        public bool Enabled { get; set; }
        public BitmapImage Icon { get; set; }
        public bool Installed { get { return _inst; } }
        public string LocalPath { get; set; }

        private bool _inst;

        public Game(string pTitle, string pIdentifier, string pDesc, string pIcon, string pLoc, string pCheck, string pExec, string pArgs, bool pEnabled, string pSessionID)
        {
            Title = pTitle;
            Description = pDesc;
            Location = pLoc;
            Enabled = pEnabled;
            Identifier = pIdentifier;
            CheckEXE = pCheck;
            Executable = pExec;
            Arguments = pArgs;

            DownloadImage(pIcon, pSessionID);
        }

        public void Check()
        {
            _inst = false;
            LocalPath = "";
            try
            {
                if (Registry.CurrentUser.OpenSubKey("SOFTWARE\\Emulator Nexus\\Games\\" + this.Identifier) != null)
                    _inst = true;
            }
            finally
            {
                Registry.CurrentUser.Close();
            }

            try
            {
                if (_inst)
                {
                    LocalPath = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Emulator Nexus\\Games\\" + this.Identifier).GetValue("installation_path").ToString();
                    if (!File.Exists(LocalPath + "\\" + Executable) || !File.Exists(LocalPath + "\\" + CheckEXE))
                        LocalPath = "";
                }
            }
            finally
            {
                if (_inst)
                    Registry.CurrentUser.Close();
            }
        }

        public void CreateKeys(string pGamePath)
        {
            if (!_inst)
            {
                Registry.CurrentUser.CreateSubKey("SOFTWARE\\Emulator Nexus\\Games\\" + this.Identifier);
                Registry.CurrentUser.Close();
            }
            pGamePath = Path.GetDirectoryName(pGamePath);
            _inst = true;
            Registry.CurrentUser.OpenSubKey("SOFTWARE\\Emulator Nexus\\Games\\" + this.Identifier, true).SetValue("installation_path", pGamePath);
            Registry.CurrentUser.Close();
            LocalPath = pGamePath;
        }

        private void DownloadImage(string imgURL, string sessionID)
        {
            var remoteUri = imgURL + "?s=" + sessionID;
            WebClient imageDownloader = new WebClient();
            byte[] imageData = imageDownloader.DownloadData(remoteUri);

            MemoryStream imageStream = new MemoryStream(imageData);
            BitmapImage gameIcon = new BitmapImage();
            gameIcon.BeginInit();
            gameIcon.StreamSource = imageStream;
            gameIcon.EndInit();

            Icon = gameIcon;
        }

    }
}
