using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Compression;

namespace UpdateBuilder
{
    class Program
    {
        static void Main(string[] args)
        {
            string gPath = "";
            string dPath = "";
            do
            {
                Console.Clear();
                Console.WriteLine("Select the source directory:");
                gPath = Console.ReadLine();
            }
            while (!Directory.Exists(gPath));

            Console.Clear();
            Console.WriteLine("Select the destination directory:");
            dPath = Console.ReadLine();

            if (!Directory.Exists(dPath))
            {
                DirectoryInfo outDir = new DirectoryInfo(dPath);
                CreateDirectory(outDir);
            }
            else
            {
                DirectoryInfo outDirectory = new DirectoryInfo(dPath);
                foreach (System.IO.FileInfo file in outDirectory.GetFiles()) file.Delete();
                foreach (System.IO.DirectoryInfo subDirectory in outDirectory.GetDirectories()) subDirectory.Delete(true);
            }

            Console.Clear();

            string[] uList = Directory.GetFiles(gPath, "*", SearchOption.AllDirectories);

            FileStream cStream = new FileStream(dPath + "\\caches.info", FileMode.Create);
            StreamWriter cWriter = new StreamWriter(cStream);
            bool first = true;
            foreach (string uFile in uList)
            {
                Console.WriteLine("Compressing file: {0}", Path.GetFileName(uFile));
                cWriter.Write(String.Format("{2}{0}\"{1}", uFile.Replace(gPath, "").TrimStart('\\'), GetSHA1Hash(uFile), first ? "" : "|"));
                if (first)
                    first = false;
                if (!Directory.Exists(Path.GetDirectoryName(dPath + uFile.Replace(gPath, ""))))
                {
                    Console.WriteLine("Creating dir: {0}", Path.GetDirectoryName(dPath + uFile.Replace(gPath, "")));
                    DirectoryInfo fDir = new DirectoryInfo(Path.GetDirectoryName(dPath + uFile.Replace(gPath, "")));
                    CreateDirectory(fDir);
                }
                cWriter.Flush();
                Compress(uFile, dPath + uFile.Replace(gPath, "") + ".nexus");
            }

            System.Diagnostics.Process.Start(dPath);
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
            catch { }

            return (strResult);
        }

        public static void Compress(string strPath, string dstFile)
        {
            DateTime current;
            FileStream fsIn = null;
            FileStream fsOut = null;
            GZipStream gzip = null;
            byte[] buffer;
            int count = 0;
            try
            {
                current = DateTime.Now;
                
                fsOut = new FileStream(dstFile, FileMode.Create, FileAccess.Write, FileShare.None);
                gzip = new GZipStream(fsOut, CompressionMode.Compress, true);
                fsIn = new FileStream(strPath, FileMode.Open, FileAccess.Read, FileShare.Read);
                buffer = new byte[fsIn.Length];
                count = fsIn.Read(buffer, 0, buffer.Length);
                fsIn.Close();
                fsIn = null;

                // compress to the destination file
                gzip.Write(buffer, 0, buffer.Length);
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
                }
            }
        }

        public static void CreateDirectory(DirectoryInfo dirInfo)
        {
            if (dirInfo.Parent != null) CreateDirectory(dirInfo.Parent);
            if (!dirInfo.Exists) dirInfo.Create();
        }
    }
}
