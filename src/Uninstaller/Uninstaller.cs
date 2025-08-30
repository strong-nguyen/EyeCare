using Microsoft.Win32;
using System;
using System.ComponentModel;
using System.Configuration.Install;

namespace Uninstaller
{
    [RunInstaller(true)]
    public class UninstallAction : Installer
    {
        public override void Uninstall(System.Collections.IDictionary savedState)
        {
            string subKey = @"Software\Microsoft\Windows\CurrentVersion\Run";
            // Create or open the subkey
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(subKey))
            {
                if (key != null)
                {
                    key.DeleteValue("TakeABreak", throwOnMissingValue: false);
                }
            }
        }
    }
}
