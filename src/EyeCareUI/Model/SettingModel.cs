using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EyeCareUI.Model
{
    internal class SettingModel
    {
        // By default, it follow Podomoro rule
        public int BreakTimeMinutes { get; set; } = 25;  // Take a break after 25m

        public int CountdownTimeMinutes { get; set; } = 5;  // Relax 5m

        public bool IsAutoStart { get; set; } = true;  // Startup with Windows by default
    }
}
