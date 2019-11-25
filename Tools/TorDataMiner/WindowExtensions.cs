using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace TorDataMiner
{
    public static class WindowExtensions
    {
        [StructLayout(LayoutKind.Sequential)]
        private struct MARGINS
        {
            public int cxLeftWidth;      // width of left border that retains its size
            public int cxRightWidth;     // width of right border that retains its size
            public int cyTopHeight;      // height of top border that retains its size
            public int cyBottomHeight;   // height of bottom border that retains its size
        };

        [DllImport("DwmApi.dll")]
        private static extern int DwmExtendFrameIntoClientArea(IntPtr hwnd, ref MARGINS pMarInset);

        private const int GWL_STYLE = -16;
        private const int GWL_EXSTYLE = -20;
        private const int WS_EX_DLGMODALFRAME = 0x00000001;

        private const int WS_SYSMENU = 0x80000;
        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);
        [DllImport("user32.dll")]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        public static void HideCloseButton(this Window Win)
        {
            // Get the window handle
            IntPtr mainWindowPtr = new WindowInteropHelper(Win).Handle;

            // Hide the close button
            SetWindowLong(mainWindowPtr, GWL_STYLE, GetWindowLong(mainWindowPtr, GWL_STYLE) & ~WS_SYSMENU);

            // Hide Icon
            int extendedStyle = GetWindowLong(mainWindowPtr, GWL_EXSTYLE);
            SetWindowLong(mainWindowPtr, GWL_EXSTYLE, extendedStyle | WS_EX_DLGMODALFRAME);
        }

        public static void ExtendGlassHook(this Window Win)
        {
            Win.Loaded += delegate(object sender, RoutedEventArgs e)
            {
                try
                {
                    // Get the window handle
                    IntPtr mainWindowPtr = new WindowInteropHelper(Win).Handle;
                    HwndSource mainWindowSrc = HwndSource.FromHwnd(mainWindowPtr);

                    // Make everything glass-y
                    mainWindowSrc.CompositionTarget.BackgroundColor = System.Windows.Media.Colors.Transparent;

                    // Extend to the whole window
                    MARGINS margins = new MARGINS();
                    margins.cxLeftWidth = -1;
                    margins.cxRightWidth = 0;
                    margins.cyBottomHeight = 0;
                    margins.cyTopHeight = 0;

                    int hr = DwmExtendFrameIntoClientArea(mainWindowSrc.Handle, ref margins);
                    if (hr >= 0)
                        Win.Background = System.Windows.Media.Brushes.Transparent;
                }
                catch (DllNotFoundException) // We are running XP - make everything white
                {
                    Application.Current.MainWindow.Background = System.Windows.Media.Brushes.White;
                }
            };
        }

        public static void ExtendGlass(this Window Win)
        {
            try
            {
                // Get the window handle
                IntPtr mainWindowPtr = new WindowInteropHelper(Win).Handle;
                HwndSource mainWindowSrc = HwndSource.FromHwnd(mainWindowPtr);

                // Make everything glass-y
                mainWindowSrc.CompositionTarget.BackgroundColor = System.Windows.Media.Colors.Transparent;

                // Extend to the whole window
                MARGINS margins = new MARGINS();
                margins.cxLeftWidth = -1;
                margins.cxRightWidth = 0;
                margins.cyBottomHeight = 0;
                margins.cyTopHeight = 0;

                int hr = DwmExtendFrameIntoClientArea(mainWindowSrc.Handle, ref margins);
                if (hr >= 0)
                    Win.Background = System.Windows.Media.Brushes.Transparent;
            }
            catch (DllNotFoundException) // We are running XP - make everything white
            {
                Application.Current.MainWindow.Background = System.Windows.Media.Brushes.White;
            }
        }
    }
}
