using System;
using System.Collections.Generic;
using System.IO;
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
using System.Windows.Media.Animation;


namespace NexusLauncher.Controls
{
    /// <summary>
    /// Interaction logic for GameItem.xaml
    /// </summary>
    public partial class GameItem : UserControl
    {
        public Game LinkedGame { get; set; }

        public GameItem(Game pGame)
        {
            InitializeComponent();

            MemoryStream frameStream = new MemoryStream();
            NexusLauncher.Properties.Resources.game_frame.Save(frameStream, System.Drawing.Imaging.ImageFormat.Png);
            frameStream.Position = 0;

            BitmapImage frameBitmap = new BitmapImage();
            frameBitmap.BeginInit();
            frameBitmap.StreamSource = frameStream;
            frameBitmap.EndInit();

            this.frameImage.Source = frameBitmap;
            this.frameImage.Opacity = 0.6;
            this.gameImage.Opacity = 0.6;
            this.gameImage.Source = pGame.Icon;
            this.LinkedGame = pGame;
        }

        private void frameImage_MouseEnter(object sender, MouseEventArgs e)
        {
            Storyboard progStory = new Storyboard();
            DoubleAnimation progAnimation = new DoubleAnimation();
            progAnimation.From = 0.6;
            progAnimation.To = 1;
            progAnimation.Duration = new Duration(TimeSpan.FromSeconds(0.15));
            progStory.Children.Add(progAnimation);
            Storyboard.SetTargetProperty(progAnimation, new PropertyPath(ProgressBar.OpacityProperty));
            progStory.Begin(this.frameImage);
            progStory.Begin(this.gameImage);
        }

        private void frameImage_MouseLeave(object sender, MouseEventArgs e)
        {
            Storyboard progStory = new Storyboard();
            DoubleAnimation progAnimation = new DoubleAnimation();
            progAnimation.From = 1;
            progAnimation.To = 0.6;
            progAnimation.Duration = new Duration(TimeSpan.FromSeconds(0.15));
            progStory.Children.Add(progAnimation);
            Storyboard.SetTargetProperty(progAnimation, new PropertyPath(ProgressBar.OpacityProperty));
            progStory.Begin(this.frameImage);
            progStory.Begin(this.gameImage);
        }

    }
}
