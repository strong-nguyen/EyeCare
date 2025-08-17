using CommunityToolkit.Mvvm.DependencyInjection;
using EyeCareUI.View;
using EyeCareUI.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;
using Application = System.Windows.Application;

namespace EyeCareUI.Services
{
    internal class TimerService
    {
        private DispatcherTimer _takeBreakTimer;

        private DispatcherTimer _countdownTimer;

        private readonly WindowService _windowService = Ioc.Default.GetRequiredService<WindowService>();

        private readonly SettingService _settingService = Ioc.Default.GetRequiredService<SettingService>();

        public TimerService()
        {
            _takeBreakTimer = new DispatcherTimer();
            _takeBreakTimer.Interval = TimeSpan.FromMinutes(_settingService.GetBreakTimeMinutes());  // Depend on app config
            _takeBreakTimer.Tick += _takeBreakTimer_Tick;

            _countdownTimer = new DispatcherTimer();
            _countdownTimer.Interval = TimeSpan.FromSeconds(1);  // Update each 1s
            _countdownTimer.Tick += _countdownTimer_Tick;
        }

        private void _countdownTimer_Tick(object? sender, EventArgs e)
        {
            var countdownVM = Ioc.Default.GetRequiredService<CountdownViewModel>();
            countdownVM.CountdownSecond--;

            if (countdownVM.CountdownSecond == 0)
            {
                _countdownTimer.Stop();
                _takeBreakTimer.Start();

                countdownVM.ResetCountdown();

               Application.Current.Dispatcher.BeginInvoke(() =>
                {
                    _windowService.ShowWindow("CountdownWindow", false);
                });
            }
        }

        private void _takeBreakTimer_Tick(object? sender, EventArgs e)
        {
            _takeBreakTimer.Stop();
            _windowService.ShowWindow("CountdownWindow", true);

            _countdownTimer.Start();
        }

        public void OnStartApp()
        {
            _takeBreakTimer.Start();
        }

        public void OnQuitApp()
        {
            _takeBreakTimer.Stop();
            _countdownTimer.Stop();
        }

        public void OnUpdateSetting()
        {
            _takeBreakTimer.Interval = TimeSpan.FromMinutes(_settingService.GetBreakTimeMinutes());
        }

        public void OnExitCountdown()
        {
            _countdownTimer.Stop();
            _takeBreakTimer.Start();
        }

        // Sometime user want to take a break directly, not by timer
        public void OnShowCountdownDirectly()
        {
            _takeBreakTimer.Stop();
            _countdownTimer.Start();
        }
    }
}
