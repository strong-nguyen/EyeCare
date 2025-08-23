using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace EyeCareUI.ViewModel
{
    internal partial class AboutViewModel : ObservableObject
    {
        public Action? CloseAction { get; set; }

        public string Version => "1.0.0.0";

        [RelayCommand]
        private void ThankYou()
        {
            CloseAction?.Invoke();
        }
    }
}
