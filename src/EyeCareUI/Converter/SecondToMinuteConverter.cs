using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace EyeCareUI.Converter
{
    internal class SecondToMinuteConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            int second = (int)value;
            int remainSecond = second % 60;
            int minutes = second / 60;

            string formatedTime;
            if (minutes < 10)
            {
                formatedTime = $"{minutes:D2}:{remainSecond:D2}";
            }
            else
            {
                formatedTime = $"{minutes}:{remainSecond:D2}";
            }

            return formatedTime;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
