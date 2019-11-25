using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Web;
using Ookii.Dialogs.Wpf;
using System.Net;
using System.Threading;
using System.ComponentModel;

namespace NexusLauncher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Utils.ClearFiles();
            Utils.Init(SetStatus, UpdateProgress);
            this.Height = 250;
            this.Hide();
            this.ExtendGlassHook();
            Games = new List<Game>();
            ShowLogin();
        }

        public static string SessionID = null;
        public static int UserID = -1;
        private List<Game> Games;
        private bool IsUpdating = false;

        private void ShowLogin()
        {
            bool Cancelled = false;
            using (CredentialDialog dialog = new CredentialDialog())
            {
                dialog.WindowTitle = "Login to Emulator Nexus";
                dialog.MainInstruction = "Please login using your Emulator Nexus account.";
                dialog.Content = "Login with your Emulator Nexus account to access the Launcher.\nIf you don't have an account yet register now on EmulatorNexus.com";
                dialog.ShowSaveCheckBox = true;
                dialog.ShowUIForSavedCredentials = true;
                dialog.Target = "Emulator_Nexus_Launcher";

                while(!Cancelled)
                {
                    if (dialog.ShowDialog(this))
                    {
                        CheckCredentials(dialog.Credentials.UserName, dialog.Credentials.Password);

                        dialog.ConfirmCredentials(SessionID != null);

                        if (SessionID != null)
                            break;
                    }
                    else
                    {
                        Cancelled = true;
                    }
                }
            }

            if (Cancelled || SessionID == null)
            {
                this.Close();
                return;
            }

            this.Show();

            SelfUpdate.Check(GetGames);
        }

        void GetGames(bool hasUpdates)
        {
            if (hasUpdates)
            {
                // Expand the window
                StartAnimation(250, 290);
                SelfUpdate.Perform();
            }
            else
            {
                BackgroundWorker GameWorker = new BackgroundWorker();
                GameWorker.WorkerReportsProgress = true;
                GameWorker.DoWork += new DoWorkEventHandler(GameWorker_DoWork);
                GameWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(GameWorker_RunWorkerCompleted);
                GameWorker.ProgressChanged += new ProgressChangedEventHandler(GameWorker_ProgressChanged);

                GameWorker.RunWorkerAsync();
            }
        }

        void GameWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            string[] info = e.UserState as string[];
            Games.Add(new Game(info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7], (info[8] == "1") ? true : false, SessionID));
        }

        void GameWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            this.gameLoadCtl.Visibility = System.Windows.Visibility.Hidden;
            foreach (Game nGame in Games)
            {
                Controls.GameItem TempControl = new Controls.GameItem(nGame);
                TempControl.MouseEnter += new MouseEventHandler(TempControl_MouseEnter);
                TempControl.MouseLeave += new MouseEventHandler(TempControl_MouseLeave);
                TempControl.PreviewMouseLeftButtonUp += new MouseButtonEventHandler(TempControl_PreviewMouseLeftButtonUp);
                this.gamesPanel.Children.Add(TempControl);
            }
            Utils.SetStatus("Select a Game");
        }

        void TempControl_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (IsUpdating)
                return;
            IsUpdating = true;
            this.gamesPanel.IsEnabled = false;
            Controls.GameItem GameItem = sender as Controls.GameItem;
            if (!GameItem.LinkedGame.Enabled)
            {
                using (TaskDialog dialog = new TaskDialog())
                {
                    dialog.WindowTitle = "Action Failed";
                    dialog.MainInstruction = "Could not launch the selected game.";
                    dialog.Content = "The specified game is currently not supported. Please try again at a later time.";
                    TaskDialogButton okButton = new TaskDialogButton(ButtonType.Ok);
                    dialog.Buttons.Add(okButton);
                    dialog.ShowDialog(this);
                }
                this.gamesPanel.IsEnabled = true;
                return;
            }

            LaunchGame(GameItem);
            IsUpdating = false;
        }

        private void LaunchGame(Controls.GameItem pItem)
        {
            Utils.SetStatus("Checking '" + pItem.LinkedGame.Title + "'...");
            pItem.LinkedGame.Check();

            if (!pItem.LinkedGame.Installed || (pItem.LinkedGame.Installed && pItem.LinkedGame.LocalPath == ""))
            {
                bool GotFile = false;
                VistaOpenFileDialog dialog = new VistaOpenFileDialog();
                dialog.CheckFileExists = true;
                dialog.Title = "Select your '" + pItem.LinkedGame.Title + "' Executable.";
                dialog.Filter = "Game Executable|" + System.IO.Path.GetFileName(pItem.LinkedGame.CheckEXE);
                GotFile = (bool)dialog.ShowDialog(this);

                if (!GotFile)
                    return;

                pItem.LinkedGame.CreateKeys(dialog.FileName);
            }

            StartAnimation(250, 290);
            var Updater = new GameUpdater(pItem.LinkedGame);
        }

        void TempControl_MouseEnter(object sender, MouseEventArgs e)
        {
            Utils.SetStatus((sender as Controls.GameItem).LinkedGame.Title);
        }

        void TempControl_MouseLeave(object sender, MouseEventArgs e)
        {
            Utils.SetStatus("Select a Game");
        }

        void GameWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            Utils.SetStatus("Checking for Games...");

            string gameList = Utils.DoWebRequest(String.Format("http://emulatornexus.com/sso/getgames.php?session={0}",
                SessionID));
            if (gameList.Equals("invalid", StringComparison.OrdinalIgnoreCase))
            {
                InvalidSessionError();
                return;
            }

            string[] gameIDs = gameList.Split('|');
            Utils.SetStatus("Retrieving Game Information...");

            foreach (string gameID in gameIDs)
            {
                if (gameID.Length > 0)
                {
                    string GameInfo = Utils.DoWebRequest(String.Format("http://emulatornexus.com/sso/getinfo.php?session={0}&gid={1}",
                        SessionID,
                        gameID));
                    if (!GameInfo.Equals("invalid", StringComparison.OrdinalIgnoreCase))
                    {
                        string[] info = GameInfo.Split('|');
                        (sender as BackgroundWorker).ReportProgress(0, info);
                    }
                }
            }
        }

        public void SetStatus(string pStatus)
        {
            this.statusLbl.Dispatcher.Invoke(
                System.Windows.Threading.DispatcherPriority.Normal,
                new Action(
                    delegate()
                    {
                        statusLbl.Content = pStatus;
                    }
            ));
        }

        public void UpdateProgress(double pProgress)
        {
            this.progressBar.Dispatcher.Invoke(
                System.Windows.Threading.DispatcherPriority.Normal,
                new Action(
                    delegate()
                    {
                        progressBar.Value = pProgress;
                    }
            ));
        }

        private void CheckCredentials(string username, string password)
        {
            try
            {
                string responseFromServer = Utils.DoWebRequest(String.Format("http://emulatornexus.com/sso/verify.php?username={0}&password={1}",
                    HttpUtility.UrlEncode(username),
                    HttpUtility.UrlEncode(password)));

                if (responseFromServer.Equals("invalid", StringComparison.OrdinalIgnoreCase))
                {
                    if (TaskDialog.OSSupportsTaskDialogs)
                    {
                        using (TaskDialog dialog = new TaskDialog())
                        {
                            dialog.WindowTitle = "Login Failed";
                            dialog.MainInstruction = "Login was unsuccessful";
                            dialog.Content = "The specified credentials appear to be invalid.\nPlease check your username and password and then try again.";
                            dialog.Footer = "You can register a new account by clicking <a href=\"http://emulatornexus.com/sso/register.php\">here</a>.";
                            dialog.FooterIcon = TaskDialogIcon.Information;
                            dialog.EnableHyperlinks = true;
                            TaskDialogButton okButton = new TaskDialogButton(ButtonType.Ok);
                            dialog.HyperlinkClicked += new EventHandler<HyperlinkClickedEventArgs>(dialog_HyperlinkClicked);
                            dialog.Buttons.Add(okButton);
                            dialog.ShowDialog(this);
                        }
                    }
                    else
                    {
                        MessageBox.Show(this, "The specified credentials appear to be invalid.\nPlease check your username and password and then try again.", "Login Failed");
                    }
                    return;
                }

                string[] Tokens = responseFromServer.Split('|');
                UserID = Int32.Parse(Tokens[0]);
                SessionID = Tokens[1];
            }
            catch (Exception ex)
            {
                if (TaskDialog.OSSupportsTaskDialogs)
                {
                    using (TaskDialog dialog = new TaskDialog())
                    {
                        dialog.WindowTitle = "Application Error";
                        dialog.MainInstruction = "An error has occured.";
                        dialog.Content = "There was a problem logging you in.\n\nPossible causes are:\n- Our server being unavailable\n- Your internet connection being down";
                        dialog.ExpandedInformation = ex.ToString();
                        TaskDialogButton okButton = new TaskDialogButton(ButtonType.Ok);
                        dialog.Buttons.Add(okButton);
                        dialog.ShowDialog(this);
                    }
                }
                else
                {
                    MessageBox.Show(this, "There was a problem logging you in.\n\nPossible causes are:\n- Our server being unavailable\n- Your internet connection being down", "Application Error");
                }
            }
        }

        private void InvalidSessionError()
        {
            
        }

        void dialog_HyperlinkClicked(object sender, HyperlinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start(e.Href);
        }

        void StartAnimation(double oldValue, double newValue)
        {
            double newWidth = newValue;
            DoubleAnimation animation = new DoubleAnimation();
            animation.From = oldValue;
            animation.To = newWidth;
            animation.Duration = new Duration(TimeSpan.FromSeconds(0.2));
            Storyboard story = new Storyboard();
            story.Children.Add(animation);
            Storyboard.SetTargetName(this, this.Name);
            Storyboard.SetTargetProperty(animation, new PropertyPath(Window.HeightProperty));
            story.Begin(this);

            Storyboard progStory = new Storyboard();
            DoubleAnimation progAnimation = new DoubleAnimation();
            progAnimation.From = 0;
            progAnimation.To = 1;
            progAnimation.Duration = new Duration(TimeSpan.FromSeconds(0.3));
            progStory.Children.Add(progAnimation);
            Storyboard.SetTargetProperty(progAnimation, new PropertyPath(ProgressBar.OpacityProperty));
            progStory.Begin(this.progressBar);
        }
    }
}
