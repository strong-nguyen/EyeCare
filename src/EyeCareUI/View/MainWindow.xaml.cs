using CommunityToolkit.Mvvm.DependencyInjection;
using EyeCareUI.Services;
using EyeCareUI.View;
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

namespace EyeCareUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private readonly WindowService _windowService = Ioc.Default.GetRequiredService<WindowService>();

        private readonly TimerService _timerService = Ioc.Default.GetRequiredService<TimerService>();
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            _windowService.ShowWindow("SettingWindow", true);
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            _windowService.ShowWindow("AboutWindow", true);
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            _windowService.ShowWindow("CountdownWindow", true);
            _timerService.OnShowCountdownDirectly();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}