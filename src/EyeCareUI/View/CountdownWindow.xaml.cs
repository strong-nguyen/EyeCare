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
        }
    }
}
