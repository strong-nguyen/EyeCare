using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration.Install;
using System.Diagnostics;
using System.IO;

namespace Uninstaller
{
    [RunInstaller(true)]
    public class UninstallAction : Installer
    {
        public override void Uninstall(System.Collections.IDictionary savedState)
        {
            StopApplication();
            DeleteRegistry();
            DeleteAppdataFolder();
            DeleteShortcuts();
        }

        private void StopApplication()
        {
            string processName = "Take A Break";

            foreach (Process proc in Process.GetProcessesByName(processName))
            {
                proc.Kill(); // Forcefully terminates the process
                proc.WaitForExit(); // Optional: wait until it fully exits
            }
        }

        private void DeleteRegistry()
        {
            // Delete startup with Windows registry
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

        private void DeleteAppdataFolder()
        {
            string localAppDataPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            string appDataPath = Path.Combine(localAppDataPath, "TakeABreak");
            if (Directory.Exists(appDataPath))
            {
                Directory.Delete(appDataPath, recursive: true);
            }
        }

        private void DeleteShortcuts()
        {
            string desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            string startMenuPath = Environment.GetFolderPath(Environment.SpecialFolder.StartMenu);

            List<string> shortcutPaths = new List<string>();
            shortcutPaths.Add(Path.Combine(desktopPath, "Take A Break.lnk"));
            shortcutPaths.Add(Path.Combine(startMenuPath, "Take A Break.lnk"));

            foreach (string shortcut in shortcutPaths)
            {
                if (File.Exists(shortcut))
                {
                    File.Delete(shortcut);
                }
            }
        }
    }
}
