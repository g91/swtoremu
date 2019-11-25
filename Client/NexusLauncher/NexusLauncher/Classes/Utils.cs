using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

namespace NexusLauncher
{
    public static class Utils
    {
        private static SetStatusDelegate _setStatus;
        private static UpdateProgressDelegate _updProg;

        public static void Init(SetStatusDelegate pSetStatus, UpdateProgressDelegate pUpdProg)
        {
            _setStatus = pSetStatus;
            _updProg = pUpdProg;
        }

        public static void ClearFiles()
        {
            string cPath = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            
            try
            {
                if (File.Exists(cPath + @"\nlauncher.nexus"))
                    File.Delete(cPath + @"\nlauncher.nexus");
            }
            catch { }

            try
            {
                if (File.Exists(cPath + @"\nupdate.exe"))
                    File.Delete(cPath + @"\nupdate.exe");
            }
            catch { }
        }

        public static string DoWebRequest(string url)
        {
            WebRequest request = WebRequest.Create(url);
            request.Method = "GET";
            WebResponse response = request.GetResponse();

            Stream dataStream = response.GetResponseStream();

            StreamReader reader = new StreamReader(dataStream);
            string responseFromServer = reader.ReadToEnd();

            reader.Close();
            dataStream.Close();
            response.Close();

            return responseFromServer;
        }

        public static void SetStatus(string pStatus)
        {
            _setStatus(pStatus);
        }

        public static void UpdateProgress(double pProgress)
        {
            _updProg(pProgress);
        }

        public static void CreateDirectory(this DirectoryInfo dirInfo)
        {
            if (dirInfo.Parent != null) CreateDirectory(dirInfo.Parent);
            if (!dirInfo.Exists) dirInfo.Create();
        }

        private static FileStream GetFileStream(string pathName)
        {
            return (new FileStream(pathName, FileMode.Open, FileAccess.Read));
        }

        public static string GetSHA1Hash(string pathName)
        {
            string strResult = "";
            string strHashData = "";

            byte[] arrbytHashValue;
            System.IO.FileStream oFileStream = null;

            System.Security.Cryptography.SHA1CryptoServiceProvider oSHA1Hasher =
                       new System.Security.Cryptography.SHA1CryptoServiceProvider();

            try
            {
                oFileStream = GetFileStream(pathName);
                arrbytHashValue = oSHA1Hasher.ComputeHash(oFileStream);
                oFileStream.Close();

                strHashData = System.BitConverter.ToString(arrbytHashValue);
                strHashData = strHashData.Replace("-", "");
                strResult = strHashData;
            }
            catch { } // TODO: Error handling

            return (strResult);
        }

    }
}
