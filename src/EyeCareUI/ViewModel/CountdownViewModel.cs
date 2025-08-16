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

        private readonly SettingService _settingService = Ioc.Default.GetRequiredService<SettingService>();

        private readonly TimerService _timerService = Ioc.Default.GetRequiredService<TimerService>();

        [ObservableProperty]
        int _countdownSecond;

        public CountdownViewModel()
        {
            ResetCountdown();
        }

        [RelayCommand]
        private void ExitCountdown()
        {
            ResetCountdown();
            _timerService.OnExitCountdown();
            _windowService.ShowWindow("CountdownWindow", false);
        }

        public void ResetCountdown()
        {
            CountdownSecond = _settingService.GetCountdownTimeMinutes() * 60;
        }
    }
}
