using CommunityToolkit.Mvvm.DependencyInjection;
using System.Configuration;
using System.Data;
using System.Windows;
using Microsoft.Extensions.DependencyInjection;
using EyeCareUI.ViewModel;
using PipeCS;
using EyeCareUI.View;
using System.Collections.Concurrent;

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
            serviceCollections.AddSingleton<AboutViewModel>();
            serviceCollections.AddTransient<MainWindow>();

            IServiceProvider provider = serviceCollections.BuildServiceProvider();
            Ioc.Default.ConfigureServices(provider);

            _pipeServer = new PipeServer("EyeCareUIPipe", (string message)=>
            {
                _pipeMessages.Enqueue(message);
                _pipeEvent.Set();
            });

            Task.Run(() =>
            {
                _pipeServer.Start();
            });

            Task.Run(() =>
            {
                while (!_stopPipeMessageQueue)
                {
                    _pipeEvent.WaitOne();
                    if (_pipeMessages.Count != 0)
                    {
                        if (_pipeMessages.TryDequeue(out string msg))
                        {
                            HandlePipeMessage(msg);
                        }
                    }
                }
            });

            var mainWindow = Ioc.Default.GetRequiredService<MainWindow>();
            mainWindow.Show();
        }

        protected override void OnExit(ExitEventArgs e)
        {
            _pipeServer?.Stop();
            _stopPipeMessageQueue = true;
        }

        private void HandlePipeMessage(string message)
        {
            switch(message)
            {
                case "showAboutWindow":
                    Application.Current.Dispatcher.BeginInvoke(() =>
                    {
                        About about = new About();
                        about.Show();
                    });
                    break;
                case "showSettingWindow":
                    Application.Current.Dispatcher.BeginInvoke(() =>
                    {
                        Setting setting = new Setting();
                        setting.Show();
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
