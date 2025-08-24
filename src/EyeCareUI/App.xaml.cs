using CommunityToolkit.Mvvm.DependencyInjection;
using System.Configuration;
using System.Data;
using System.Windows;
using Microsoft.Extensions.DependencyInjection;
using EyeCareUI.ViewModel;
using PipeCS;
using EyeCareUI.View;
using System.Collections.Concurrent;
using EyeCareUI.Services;

namespace EyeCareUI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            var serviceCollections = new ServiceCollection();

            // Views
            serviceCollections.AddTransient<MainWindow>();
            serviceCollections.AddSingleton<CountdownWindow>();
            serviceCollections.AddSingleton<About>();
            serviceCollections.AddTransient<Setting>();

            // Services
            serviceCollections.AddSingleton<WindowService>();
            serviceCollections.AddSingleton<TimerService>();
            serviceCollections.AddSingleton<SettingService>();

            // View Models
            serviceCollections.AddSingleton<CountdownViewModel>();
            serviceCollections.AddSingleton<AboutViewModel>();
            serviceCollections.AddTransient<SettingViewModel>();

            IServiceProvider provider = serviceCollections.BuildServiceProvider();
            Ioc.Default.ConfigureServices(provider);

            var timerService = Ioc.Default.GetRequiredService<TimerService>();
            timerService.OnStartApp();

            _pipeServer = new PipeServer("EyeCareUIPipe", (string message)=>
            {
                _pipeMessages.Enqueue(message);
                _pipeEvent.Set();
            });

            Task.Run(() =>
            {
                _pipeServer?.Start();
            });

            Task.Run(() =>
            {
                while (!_stopPipeMessageQueue)
                {
                    _pipeEvent.WaitOne();
                    if (_pipeMessages.Count != 0)
                    {
                        if (_pipeMessages.TryDequeue(out string? msg))
                        {
                            HandlePipeMessage(msg);
                        }
                    }
                }
            });

            var mainWnd = Ioc.Default.GetRequiredService<MainWindow>();
            mainWnd.Show();
        }

        protected override void OnExit(ExitEventArgs e)
        {
            _pipeServer?.Stop();
            _stopPipeMessageQueue = true;
        }

        private void HandlePipeMessage(string message)
        {
            var windowService = Ioc.Default.GetRequiredService<WindowService>();
            switch(message)
            {
                case "showAboutWindow":
                    Application.Current.Dispatcher.BeginInvoke(() =>
                    {
                        windowService.ShowWindow("AboutWindow", true);
                    });
                    break;
                case "showSettingWindow":
                    Application.Current.Dispatcher.BeginInvoke(() =>
                    {
                        windowService.ShowWindow("SettingWindow", true);
                    });
                    break;
                case "showCountdownWindow":
                    Application.Current.Dispatcher.BeginInvoke(() =>
                    {
                        windowService.ShowWindow("CountdownWindow", true);
                        var timerService = Ioc.Default.GetRequiredService<TimerService>();
                        timerService.OnShowCountdownDirectly();
                    });
                    break;
                case "quit":
                    Application.Current.Dispatcher.BeginInvoke(() =>
                    {
                        Application.Current.Shutdown();
                    });
                    break;
                default:
                    break;
            }
        }

        private PipeServer? _pipeServer = null;

        private ConcurrentQueue<string> _pipeMessages = new ConcurrentQueue<string>();

        private bool _stopPipeMessageQueue = false;

        private AutoResetEvent _pipeEvent = new AutoResetEvent(false);
    }

}
