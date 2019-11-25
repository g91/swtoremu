using System;
using System.Collections.Generic;
using System.Threading;
using System.Net;
using System.Text;
using System.ComponentModel;
using System.IO;

namespace NexusLauncher
{
    public delegate void GetGamesDelegate(bool hasUpdates);
    public delegate void UpdateProgressDelegate(double pProgress);
    public delegate void SetStatusDelegate(string pStatus);

    public static class SelfUpdate
    {
        private static string updURL = "http://cdn.emulatornexus.com/u/f/";
        private static bool hasUpdate = false;
        static GetGamesDelegate _getGames;

        public static void Check(GetGamesDelegate pGetGames)
        {
            Utils.SetStatus("Checking for Launcher Updates...");
            _getGames = pGetGames;
            BackgroundWorker UpdChecker = new BackgroundWorker();
            UpdChecker.DoWork += new DoWorkEventHandler(UpdChecker_DoWork);
            UpdChecker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(UpdChecker_RunWorkerCompleted);
            UpdChecker.RunWorkerAsync();
        }

        static void UpdChecker_DoWork(object sender, DoWorkEventArgs e)
        {
            Version latestVer = new Version(Utils.DoWebRequest(String.Format("{0}launcher.info?s={1}", updURL, MainWindow.SessionID)));
            Version currentVer = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
            if (latestVer.CompareTo(currentVer) == 1)
                hasUpdate = true;
        }

        static void UpdChecker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            _getGames(hasUpdate);
        }

        // Updater

        public static void Perform()
        {
            Utils.SetStatus("Updating to the latest version...");

            WebClient updateDownloader = new WebClient();
            updateDownloader.DownloadProgressChanged += new DownloadProgressChangedEventHandler(updateDownloader_DownloadProgressChanged);
            updateDownloader.DownloadDataCompleted += new DownloadDataCompletedEventHandler(updateDownloader_DownloadDataCompleted);
            updateDownloader.DownloadDataAsync(new Uri(String.Format("{0}nlauncher.nexus?s={1}", updURL, MainWindow.SessionID)));
        }

        static void updateDownloader_DownloadDataCompleted(object sender, DownloadDataCompletedEventArgs e)
        {
            Utils.SetStatus("Download Completed. Updating...");

            byte[] dlData = e.Result;
            File.WriteAllBytes(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + @"\nlauncher.nexus", dlData);
            File.WriteAllBytes(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + @"\nupdate.exe", Properties.Resources.nupdate);

            System.Diagnostics.Process p = new System.Diagnostics.Process();
            p.StartInfo.WorkingDirectory = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            p.StartInfo.FileName = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + @"\nupdate.exe";
            p.StartInfo.Arguments = System.Diagnostics.Process.GetCurrentProcess().Id + " \"" + Path.GetFileName(System.Reflection.Assembly.GetExecutingAssembly().Location) + "\" \"nlauncher.nexus\"";
            p.Start();
        }

        static void updateDownloader_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            Utils.UpdateProgress(e.ProgressPercentage);
        }
    }
}
