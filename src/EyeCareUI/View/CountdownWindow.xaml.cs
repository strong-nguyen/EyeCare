using CommunityToolkit.Mvvm.DependencyInjection;
using EyeCareUI.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.IO;

namespace EyeCareUI.View
{
    /// <summary>
    /// Interaction logic for CountdownWindow.xaml
    /// </summary>
    public partial class CountdownWindow : Window
    {
        public CountdownWindow()
        {
            InitializeComponent();
            this.DataContext = Ioc.Default.GetRequiredService<CountdownViewModel>();

            //SetBackgroundImage();

            WindowStyle = WindowStyle.None;          // Removes title bar and borders
            ResizeMode = ResizeMode.NoResize;        // Prevents resizing
            WindowState = WindowState.Maximized;     // Maximizes to full screen
            Topmost = true;
        }

        protected override void OnActivated(EventArgs e)
        {
            base.OnActivated(e);
            SetBackgroundImage();  // Set background image each time activated to ensure Wallpaper is updated
        }

        void SetBackgroundImage()
        {
            // Get the desktop photo and set it as the background
            string keyPath = @"HKEY_CURRENT_USER\Control Panel\Desktop";
            string valueName = "WallPaper";

            object wallpaperPath = Registry.GetValue(keyPath, valueName, null);

            if (wallpaperPath == null)
            {
                // TODO: Log
                return;
            }

            string wallPaper = wallpaperPath.ToString();
            if (String.IsNullOrEmpty(wallPaper))
            {
                // TODO: Log
                return;
            }

            if (!File.Exists(wallPaper))
            {
                // TODO: Log
                return;
            }

            var brush = new ImageBrush();
            brush.ImageSource = new BitmapImage(new Uri(wallPaper, UriKind.Absolute));
            this.Background = brush;
        }
    }
}
