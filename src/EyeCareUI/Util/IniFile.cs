using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EyeCareUI.Util
{
    internal class IniFile
    {
        private string _iniFilePath = String.Empty;
        public IniFile(string iniFilePath)
        {
            _iniFilePath = iniFilePath;
        }

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string defaultValue, StringBuilder returnValue, int size, string filePath);
        public string ReadValue(string section, string key)
        {
            var result = new StringBuilder(255);
            GetPrivateProfileString(section, key, "", result, result.Capacity, _iniFilePath);
            return result.ToString();
        }

        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
        public void WriteValue(string section, string key, string value)
        {
            WritePrivateProfileString(section, key, value, _iniFilePath);
        }
    }
}
