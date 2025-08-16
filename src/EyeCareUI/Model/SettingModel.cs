using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EyeCareUI.Model
{
    internal class SettingModel
    {
        public int BreakTimeMinutes { get; set; } = 60;  // Take a break after 60m

        public int CountdownTimeMinutes { get; set; } = 5;  // Relax 5m

        public bool IsAutoStart { get; set; } = true;  // Startup with Windows by default
    }
}
