using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.DependencyInjection;
using CommunityToolkit.Mvvm.Input;
using EyeCareUI.Model;
using EyeCareUI.Services;
using EyeCareUI.Util;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace EyeCareUI.ViewModel
{
    internal partial class SettingViewModel : ObservableObject
    {
        private WindowService _windowService = Ioc.Default.GetRequiredService<WindowService>();

        private readonly SettingService _settingService = Ioc.Default.GetRequiredService<SettingService>();

        [ObservableProperty]
        string _breakTime = String.Empty;

        [ObservableProperty]
        string _relaxTime = String.Empty;

        [ObservableProperty]
        bool _isAutoStart = true;

        public SettingViewModel()
        {
            BreakTime = _settingService.GetBreakTimeMinutes().ToString();
            RelaxTime = _settingService.GetCountdownTimeMinutes().ToString();
            IsAutoStart = _settingService.IsAutoStart();
        }

        [RelayCommand]
        void OK()
        {
            bool ret = double.TryParse(BreakTime, out double breakTime);
            if (!ret)
            {
                MessageBox.Show("Break After Time is invalid format");
                return;
            }

            ret = double.TryParse(RelaxTime, out double relaxTime);
            if (!ret)
            {
                MessageBox.Show("Break In Time is invalid format");
                return;
            }

            SettingModel setting = new SettingModel { BreakTimeMinutes = (int)breakTime, CountdownTimeMinutes = (int)relaxTime, IsAutoStart = IsAutoStart };
            _settingService.UpdateConfig(setting);

            var timerService = Ioc.Default.GetRequiredService<TimerService>();
            timerService.OnUpdateSetting();

            _windowService.ShowWindow("SettingWindow", false);
        }

        [RelayCommand]
        void Cancel()
        {
            _windowService.ShowWindow("SettingWindow", false);
        }
    }
}
