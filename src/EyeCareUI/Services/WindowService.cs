using CommunityToolkit.Mvvm.DependencyInjection;
using EyeCareUI.View;
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
                    wnd = Ioc.Default.GetRequiredService<CountdownWindow>();
                    break;
                case "AboutWindow":
                    wnd = Ioc.Default.GetRequiredService<About>();
                    break;
                case "SettingWindow":
                    wnd = Ioc.Default.GetRequiredService<Setting>();
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
                wnd?.Show();
            }
            else
            {
                wnd?.Hide();
            }
        }
    }
}
