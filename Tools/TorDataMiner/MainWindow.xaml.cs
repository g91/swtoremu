using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using System.IO;
using System.Globalization;
using System.Threading;
using System.Diagnostics;

namespace TorDataMiner
{
    public enum LogLevel
    {
        Debug = 1,
        Info = 2,
        Warning = 4,
        Error = 8,
        Client = 16,
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Declarations

        private PacketList Packets;

        private struct DataUpdater
        {
            public int Position;
            public int Length;
            public int Sender;
            public int SendPort;
            public int Receiver;
            public int ReceivePort;
            public int Index;
        };

        private Int32 LocalIP = 0;

        #endregion

        #region Window Initialization and Drawing

        public MainWindow()
        {
            InitializeComponent();
            Packets = new PacketList();
            packetList.DataContext = Packets;
            // TODO: Get version from AssemblyInfo
            Log(LogLevel.Info, "Initialized The Old Republic Data Miner [TDM] version 0.1a by NoFaTe");
            Log(LogLevel.Info, "Waiting for user login.");
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            this.ExtendGlass();
            LoginBox LoginWnd = new LoginBox();
            LoginWnd.ShowDialog();
        }

        #endregion

        public void Log(LogLevel level, string text, params object[] args)
        {
            DateTime thisDate = DateTime.Now;
            CultureInfo culture = new CultureInfo("en-US");

            bool isChecked = false;
            this.debugBox.Dispatcher.Invoke(
                System.Windows.Threading.DispatcherPriority.Normal,
                new Action(
                    delegate()
                    {
                        isChecked = (bool)debugBox.IsChecked;
                    }
            ));

            if (!isChecked && level == LogLevel.Debug)
                return;

            this.consoleBox.Dispatcher.Invoke(
                System.Windows.Threading.DispatcherPriority.Normal,
                new Action(
                    delegate()
                    {
                        text = String.Format(text, args);
                        consoleBox.Text += String.Format("[{0}] {1}: {2}\r\n", thisDate.ToString("HH:mm:ss", culture), level.ToString().ToUpper(), text);
                    }
            ));

            this.consoleScroller.Dispatcher.Invoke(
                System.Windows.Threading.DispatcherPriority.Normal,
                new Action(
                    delegate()
                    {
                        consoleScroller.ScrollToBottom();
                    }
            ));
        }

        private void SetStatus(string status)
        {
            this.statusLbl.Dispatcher.Invoke(
               System.Windows.Threading.DispatcherPriority.Normal,
               new Action(
                   delegate()
                   {
                       statusLbl.Content = "Status: " + status;
                   }
           ));
        }

        private void loadDump_Click(object sender, RoutedEventArgs e)
        {
            if (!File.Exists(dumpPathBox.Text))
            {
                Log(LogLevel.Error, "Invalid file location entered.");
                return;
            }

            byte[] DumpData;
            try
            {
                DumpData = File.ReadAllBytes(dumpPathBox.Text);
            }
            catch
            {
                Log(LogLevel.Error, "Could not read dump file. Check if another process is using it.");
                return;
            }

            Packets.Clear();

            SetStatus("Parsing Dump");

            Thread DumpThread = new Thread(ParseDump);
            DumpThread.Start(DumpData);
        }

        #region Dump Parser

        private bool VerifyChecksum(byte[] pBuffer, byte pChecksum, int index = 0)
        {
            if (pChecksum == (pBuffer[index + 0] ^ pBuffer[index + 1] ^ pBuffer[index + 2] ^ pBuffer[index + 3] ^ pBuffer[index + 4]))
                return true;
            return false;
        }

        public string IntToIPv4(int inIP)
        {
            return String.Format("{3}.{2}.{1}.{0}", (byte)(inIP >> 24), (byte)(inIP >> 16), (byte)(inIP >> 8), (byte)(inIP));
        }

        private void ParseDump(object inObj)
        {
            Stopwatch ParseStopWatch = new Stopwatch();
            ParseStopWatch.Start();
            Log(LogLevel.Info, "Initialized Dump Parser.");
            byte[] Dump = inObj as byte[];
            MemoryStream Stream = new MemoryStream(Dump);
            BinaryReader Reader = new BinaryReader(Stream);

            while (Reader.BaseStream.Position < Dump.Length)
            {
                Int32 SenderIP = Reader.ReadInt32();
                Int16 SendPort = Reader.ReadInt16();
                Int32 ReceiverIP = Reader.ReadInt32();
                Int16 ReceivePort = Reader.ReadInt16();
                Reader.ReadUInt32(); // Packet Size

                byte Module = Reader.ReadByte();
                UInt32 Length = Reader.ReadUInt32();
                byte Checksum = Reader.ReadByte();

                if (VerifyChecksum(Dump, Checksum, (int)Reader.BaseStream.Position - 6))
                {
                    UInt32 Type = Reader.ReadUInt32();
                    UInt32 ID = Reader.ReadUInt32();

                    byte[] Data = new byte[0];
                    if (Length - 14 > 0)
                        Data = Reader.ReadBytes((int)Length - 14);

                    if (Module == 0x03 && LocalIP == 0)
                        LocalIP = ReceiverIP;

                    if (Module == 0x03 || Module == 0x04)
                        continue;

                    OmegaPacket TempPacket = new OmegaPacket(Type, Module, ID, Data, (SenderIP == LocalIP) ? false : true);
                    this.packetList.Dispatcher.Invoke(
                        System.Windows.Threading.DispatcherPriority.Normal,
                        new Action(
                            delegate()
                            {
                                Packets.Add(TempPacket);
                            }
                    ));

                    DataUpdater Updater = new DataUpdater();
                    Updater.Sender = SenderIP;
                    Updater.SendPort = SendPort;
                    Updater.Receiver = ReceiverIP;
                    Updater.ReceivePort = ReceivePort;
                    Updater.Position = (int)Reader.BaseStream.Position;
                    Updater.Length = Dump.Length;
                    Updater.Index = Packets.Count - 1;

                    UpdateProgress(Updater);
                }
            }
            ParseStopWatch.Stop();
            Log(LogLevel.Info, "Dump Parsing completed in {0}ms.", ParseStopWatch.Elapsed.TotalMilliseconds);
            SetStatus("Idle");
        }

        delegate void UpdateProgressCallback(DataUpdater Updater);

        private void UpdateProgress(DataUpdater Updater)
        {
            Log(LogLevel.Debug, "[{0}:{1} => {2}:{3}] [0x{4:X8}] (0x{5:X2})", 
                IntToIPv4(Updater.Sender), Updater.SendPort, IntToIPv4(Updater.Receiver), Updater.ReceivePort, Packets[Updater.Index].Type, Packets[Updater.Index].Module);

            this.gProgress.Dispatcher.Invoke(
                System.Windows.Threading.DispatcherPriority.Normal,
                new Action(
                    delegate()
                    {
                        gProgress.Value = ((float)Updater.Position / (float)Updater.Length) * 100;
                        if (gProgress.Value == 100)
                            gProgress.Value = 0;
                    }
            ));
        }

        #endregion

        private void mineBtn_Click(object sender, RoutedEventArgs e)
        {
            if (Packets.Count == 0)
            {
                Log(LogLevel.Error, "Dump data not loaded.");
                return;
            }

            // TODO: CodeDOM extension
        }
    }
}
