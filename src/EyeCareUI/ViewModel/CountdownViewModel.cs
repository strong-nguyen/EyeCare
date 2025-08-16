using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.DependencyInjection;
using CommunityToolkit.Mvvm.Input;
using EyeCareUI.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EyeCareUI.ViewModel
{
    internal partial class CountdownViewModel : ObservableObject
    {
        private readonly WindowService _windowService = Ioc.Default.GetRequiredService<WindowService>();
        [RelayCommand]
        private void ExitCountdown()
        {
            _windowService.ShowWindow("CountdownWindow", false);
        }
    }
}
