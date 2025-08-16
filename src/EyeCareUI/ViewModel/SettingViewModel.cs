using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.DependencyInjection;
using CommunityToolkit.Mvvm.Input;
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
        public Window? Wnd { get; set; }

        private WindowService _windowService = Ioc.Default.GetRequiredService<WindowService>();

        private IniFile _iniFile;

        [ObservableProperty]
        string _breakTime = String.Empty;

        [ObservableProperty]
        string _relaxTime = String.Empty;

        [ObservableProperty]
        bool _isAutoStart = true;

        public SettingViewModel()
        {
            string localAppDataPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            var configFile = Path.Combine(localAppDataPath, "EyeCare\\config.ini");
            _iniFile = new IniFile(configFile);

            ReadConfig();
        }

        [RelayCommand]
        void OK()
        {
            UpdateConfig();
            _windowService.ShowWindow("SettingWindow", false);
        }

        [RelayCommand]
        void Cancel()
        {
            _windowService.ShowWindow("SettingWindow", false);
        }

        private void UpdateConfig()
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
            }

            var breakTimeMs = (Int64)(breakTime * 60 * 1000);
            var relaxTimeMs = (Int64)(relaxTime * 60 * 1000);
            int isAutoStart = IsAutoStart ? 1 : 0;

            _iniFile.WriteValue("AppConfig", "BreakTimeMs", breakTimeMs.ToString());
            _iniFile.WriteValue("AppConfig", "RelaxTimeMs", relaxTimeMs.ToString());
            _iniFile.WriteValue("AppConfig", "IsAutoStart", isAutoStart.ToString());
        }

        private void ReadConfig()
        {
            bool ret = Int64.TryParse(_iniFile.ReadValue("AppConfig", "BreakTimeMs"), out long val1);
            if (ret)
            {
                BreakTime = (val1 / 1000 / 60).ToString();
            }

            ret = Int64.TryParse(_iniFile.ReadValue("AppConfig", "RelaxTimeMs"), out long val2);
            if (ret)
            {
                RelaxTime = (val2 / 1000 / 60).ToString();
            }

            ret = int.TryParse(_iniFile.ReadValue("AppConfig", "IsAutoStart"), out int val3);
            if (ret)
            {
                IsAutoStart = (val3 == 1);
            }
        }
    }
}
