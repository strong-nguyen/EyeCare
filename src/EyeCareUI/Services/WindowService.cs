using CommunityToolkit.Mvvm.DependencyInjection;
using EyeCareUI.View;
using EyeCareUI.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace EyeCareUI.Services
{
    internal class WindowService
    {
        public void ShowWindow(string windowName, bool isShow)
        {
            Window? wnd = null;
            switch (windowName)
            {
                case "CountdownWindow":
                    // Singleton
                    wnd = Ioc.Default.GetRequiredService<CountdownWindow>();
                    break;
                case "AboutWindow":
                    wnd = Application.Current.Windows.OfType<About>().FirstOrDefault();
                    if (wnd == null)
                    {
                        wnd = Ioc.Default.GetRequiredService<About>();
                    }
                    break;
                case "SettingWindow":
                    wnd = Application.Current.Windows.OfType<Setting>().FirstOrDefault();
                    if (wnd == null)
                    {
                        wnd = Ioc.Default.GetRequiredService<Setting>();
                    }
                    break;
                default:
                    break;
            }

            if (wnd == null)
            {
                return;
            }

            if (isShow)
            {
                if (windowName == "CountdownWindow")  // Before show countdow, we should reset the countdown value
                {
                    var vm = Ioc.Default.GetRequiredService<CountdownViewModel>();
                    vm.ResetCountdown();
                }

                wnd.Show();
                if (wnd.WindowState == WindowState.Minimized)
                {
                    wnd.Activate();
                }
            }
            else
            {
                if (windowName == "SettingWindow" || windowName == "AboutWindow")
                {
                    wnd?.Close();
                }
                else
                {
                    wnd?.Hide();
                }
            }
        }
    }
}
