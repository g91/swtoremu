using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.IO;
using System.IO.Compression;
using System.Net;
using System.Threading;
using System.Windows;

namespace NexusLauncher
{
    class GameUpdater
    {
        private Game _game;
        private BackgroundWorker _worker;
        private Dictionary<string, string> _uFiles;
        
        public GameUpdater(Game pGame)
        {
            _game = pGame;

            _worker = new BackgroundWorker();
            _worker.WorkerReportsProgress = true;
            _worker.DoWork += new DoWorkEventHandler(Worker_DoWork);
            _worker.ProgressChanged += new ProgressChangedEventHandler(Worker_ProgressChanged);
            _worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(Worker_RunWorkerCompleted);
            _worker.RunWorkerAsync();

            _uFiles = new Dictionary<string, string>();
        }

        private class WorkUpdater
        {
            public string Status;
            public double Progress;

            public WorkUpdater(string pStatus, double pProg = -1)
            {
                Status = pStatus;
                Progress = pProg;
            }
        }

        void Worker_DoWork(object sender, DoWorkEventArgs e)
        {
            _worker.ReportProgress(0, new WorkUpdater("Checking for Game Updates...", 0));
            DownloadCaches();

            if (_uFiles.Count > 0)
            {
                int count = 0;
                foreach (KeyValuePair<string, string> uFile in _uFiles)
                    if (!CheckFile(uFile.Key, uFile.Value))
                    {
                        _worker.ReportProgress(0, new WorkUpdater("Downloading Updates...", (double)((double)count / (double)_uFiles.Count) * 100d));
                        UpdateFile(uFile.Key);
                        count++;
                    }
                _worker.ReportProgress(0, new WorkUpdater("Finished Updating. Launching...", 100));
            }
            else
            {
                _worker.ReportProgress(0, new WorkUpdater("Game is Up-To-Date. Launching...", 100));
            }
        }

        void Worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            WorkUpdater Updater = e.UserState as WorkUpdater;
            if (Updater.Status.Length > 0)
                Utils.SetStatus(Updater.Status);
            if (Updater.Progress >= 0)
                Utils.UpdateProgress(Updater.Progress);
        }

        void Worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            FinalLaunch();
        }

        private void DownloadCaches()
        {
            string[] sCaches = Utils.DoWebRequest(String.Format("{0}caches.info?s={1}", _game.Location, MainWindow.SessionID)).Split('|');
            foreach (string sCache in sCaches)
            {
                string[] gFile = sCache.Split('"');
                _uFiles.Add(gFile[0], gFile[1]);
            }
        }

        private bool CheckFile(string pPath, string pHash)
        {
            if (File.Exists(_game.LocalPath + "\\" + pPath))
                if (Utils.GetSHA1Hash(_game.LocalPath + "\\" + pPath).Equals(pHash, StringComparison.OrdinalIgnoreCase))
                    return true;
            return false;
        }

        private void UpdateFile(string pPath)
        {
            //MessageBox.Show("Updating file: " + pPath);
            if (File.Exists(_game.LocalPath + "\\" + pPath))
                File.Delete(_game.LocalPath + "\\" + pPath);

            if (!Directory.Exists(Path.GetDirectoryName(_game.LocalPath + "\\" + pPath)))
            {
                var newDir = new DirectoryInfo(Path.GetDirectoryName(_game.LocalPath + "\\" + pPath));
                newDir.CreateDirectory();
            }

            AutoResetEvent waiter = new AutoResetEvent(false);
            WebClient fileDownloader = new WebClient();
            fileDownloader.DownloadProgressChanged += new DownloadProgressChangedEventHandler(fileDownloader_DownloadProgressChanged);
            fileDownloader.DownloadFileCompleted += (f, a) => waiter.Set();
            fileDownloader.DownloadFileAsync(new Uri(String.Format("{0}{1}.nexus?s={2}", _game.Location, pPath, MainWindow.SessionID)), _game.LocalPath + "\\" + pPath + ".nexus", waiter);
            waiter.WaitOne();

            DecompressFile(String.Format("{0}\\{1}", _game.LocalPath, pPath));
        }

        void fileDownloader_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            //_worker.ReportProgress(0, new WorkUpdater("", e.ProgressPercentage));
        }

        private void DecompressFile(string pPath)
        {
            string dstFile = "";

            FileStream fsIn = null;
            FileStream fsOut = null;
            GZipStream gzip = null;
            const int bufferSize = 4096;
            byte[] buffer = new byte[bufferSize];
            int count = 0;

            try
            {
                dstFile = pPath;
                fsIn = new FileStream(pPath + ".nexus", FileMode.Open, FileAccess.Read, FileShare.Read);
                fsOut = new FileStream(dstFile, FileMode.Create, FileAccess.Write, FileShare.None);
                gzip = new GZipStream(fsIn, CompressionMode.Decompress, true);
                while (true)
                {
                    count = gzip.Read(buffer, 0, bufferSize);
                    if (count != 0)
                    {
                        fsOut.Write(buffer, 0, count);
                    }
                    if (count != bufferSize)
                    {
                        // have reached the end
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                // handle or display the error 
                System.Diagnostics.Debug.Assert(false, ex.ToString());
            }
            finally
            {
                if (gzip != null)
                {
                    gzip.Close();
                    gzip = null;
                }
                if (fsOut != null)
                {
                    fsOut.Close();
                    fsOut = null;
                }
                if (fsIn != null)
                {
                    fsIn.Close();
                    fsIn = null;
                    File.Delete(pPath + ".nexus");
                }
            }
        }

        public void FinalLaunch()
        {
            System.Diagnostics.Process p = new System.Diagnostics.Process();
            p.StartInfo.WorkingDirectory = Path.GetDirectoryName(String.Format("{0}\\{1}", _game.LocalPath, _game.Executable));
            p.StartInfo.FileName = String.Format("{0}\\{1}", _game.LocalPath, _game.Executable);
            p.StartInfo.Arguments = _game.Arguments; // TODO: Language checks
            p.Start();
            Application.Current.Shutdown();
        }
    }
}
