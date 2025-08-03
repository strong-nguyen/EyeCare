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

        [RelayCommand]
        private void ThankYou()
        {
            CloseAction?.Invoke();
        }
    }
}
