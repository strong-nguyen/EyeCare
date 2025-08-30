using EyeCareUI.Model;
using EyeCareUI.Util;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EyeCareUI.Services
{
    internal class SettingService
    {
        private SettingModel _settings;

        public SettingModel Settings
        {
            get { return _settings; }
        }

        private IniFile _iniFile;

        public SettingService()
        {
            _settings = new SettingModel();
            string localAppDataPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            var configFile = Path.Combine(localAppDataPath, TakeABreakDefine.AppName, TakeABreakDefine.ConfigFileName);
            _iniFile = new IniFile(configFile);

            ReadConfig();
        }

        public int GetBreakTimeMinutes()
        {
            return _settings.BreakTimeMinutes;
        }

        public int GetCountdownTimeMinutes()
        {
            return _settings.CountdownTimeMinutes;
        }

        public bool IsAutoStart()
        {
            return _settings.IsAutoStart;
        }

        public void UpdateConfig(SettingModel settingModel)
        {
            _settings = settingModel;

            int autoStart = _settings.IsAutoStart ? 1 : 0;
            _iniFile.WriteValue("AppConfig", "BreakTimeMinute", _settings.BreakTimeMinutes.ToString());
            _iniFile.WriteValue("AppConfig", "RelaxTimeMinute", _settings.CountdownTimeMinutes.ToString());
            _iniFile.WriteValue("AppConfig", "IsAutoStart", autoStart.ToString());
        }

        public void ReadConfig()
        {
            bool ret = int.TryParse(_iniFile.ReadValue("AppConfig", "BreakTimeMinute"), out int val1);
            if (ret)
            {
                _settings.BreakTimeMinutes = val1;
            }

            ret = int.TryParse(_iniFile.ReadValue("AppConfig", "RelaxTimeMinute"), out int val2);
            if (ret)
            {
                _settings.CountdownTimeMinutes = val2;
            }

            ret = int.TryParse(_iniFile.ReadValue("AppConfig", "IsAutoStart"), out int val3);
            if (ret)
            {
                _settings.IsAutoStart = (val3 == 1);
            }
        }
    }
}
