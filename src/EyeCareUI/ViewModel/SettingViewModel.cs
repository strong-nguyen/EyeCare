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
using Microsoft.Win32;
using System.Xml.Linq;

namespace EyeCareUI.ViewModel
{
    delegate Window? GetOwnerWindow();

    internal partial class SettingViewModel : ObservableObject
    {
        public GetOwnerWindow? GetOwner { get; set; }

        private WindowService _windowService = Ioc.Default.GetRequiredService<WindowService>();

        private readonly SettingService _settingService = Ioc.Default.GetRequiredService<SettingService>();

        string _breakTime = String.Empty;

        string _relaxTime = String.Empty;

        bool _isAutoStart = true;

        public string BreakTime
        {
            get
            {
                return _breakTime;
            }

            set
            {
                if (_breakTime != value)
                {
                    _breakTime = value;
                    OnPropertyChanged();

                    CheckUserSettingHasChanged();
                }
            }
        }

        public string RelaxTime
        {
            get
            {
                return _relaxTime;
            }

            set
            {
                if (_relaxTime != value)
                {
                    _relaxTime = value;
                    OnPropertyChanged();

                    CheckUserSettingHasChanged();
                }
            }
        }

        public bool IsAutoStart
        {
            get
            {
                return _isAutoStart;
            }

            set
            {
                if (_isAutoStart != value)
                {
                    _isAutoStart = value;
                    OnPropertyChanged();

                    CheckUserSettingHasChanged();
                }
            }
        }

        public SettingViewModel()
        {
            BreakTime = _settingService.GetBreakTimeMinutes().ToString();
            RelaxTime = _settingService.GetCountdownTimeMinutes().ToString();
            IsAutoStart = _settingService.IsAutoStart();

            CanApplySetting = false;
        }

        [ObservableProperty]
        [NotifyCanExecuteChangedFor(nameof(OKCommand))]
        bool _canApplySetting;

        bool CheckUserSettingHasChanged()
        {
            if (_settingService.GetBreakTimeMinutes().ToString() != BreakTime)
            {
                CanApplySetting = true;
                return true;
            }

            if (_settingService.GetCountdownTimeMinutes().ToString() != RelaxTime)
            {
                CanApplySetting = true;
                return true;
            }

            if (_settingService.IsAutoStart() != IsAutoStart)
            {
                CanApplySetting = true;
                return true;
            }

            CanApplySetting = false;
            return false;
        }

        [RelayCommand(CanExecute = nameof(CanApplySetting))]
        void OK()
        {
            bool ret = double.TryParse(BreakTime, out double breakTime);
            if (!ret)
            {
                MessageBox.Show(GetOwner?.Invoke(), "Take A Break After Time is invalid format", "Take A Break", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            ret = double.TryParse(RelaxTime, out double relaxTime);
            if (!ret)
            {
                MessageBox.Show(GetOwner?.Invoke(), "Break In Time is invalid format", "Take A Break", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            SettingModel setting = new SettingModel { BreakTimeMinutes = (int)breakTime, CountdownTimeMinutes = (int)relaxTime, IsAutoStart = IsAutoStart };
            _settingService.UpdateConfig(setting);

            var timerService = Ioc.Default.GetRequiredService<TimerService>();
            timerService.OnUpdateSetting();

            SetAutoStartWithWindows(setting.IsAutoStart);

            _windowService.ShowWindow("SettingWindow", false);
        }

        bool SetAutoStartWithWindows(bool isAutoStart)
        {
            string subKey = @"Software\Microsoft\Windows\CurrentVersion\Run";
            // Create or open the subkey
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(subKey))
            {
                if (key != null)
                {
                    if (isAutoStart)
                    {
                        // Set a value inside the key
                        key.SetValue(TakeABreakDefine.AppName, TakeABreakDefine.TakeABreakExeInstallPath, RegistryValueKind.String);
                        return true;
                    }
                    else
                    {
                        key.DeleteValue(TakeABreakDefine.AppName, throwOnMissingValue: false);
                        return true;
                    }
                }
            }

            return false;
        }

        [RelayCommand]
        void Cancel()
        {
            _windowService.ShowWindow("SettingWindow", false);
        }
    }
}
