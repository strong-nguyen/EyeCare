#include "pch.h"
#include "Common.h"


namespace Common
{
	std::wstring FormatTime(long seconds)
	{
		int minutes = 0;
		while (seconds >= 60)
		{
			seconds -= 60;
			++minutes;
		}
		
		int hours = 0;
		while (minutes >= 60)
		{
			minutes -= 60;
			++hours;
		}

		if (minutes == 0)
		{
			return std::format(L"{}s", seconds);
		}
		else if (hours == 0)
		{
			return std::format(L"{}m : {}s", minutes, seconds);
		}
		else
		{
			return std::format(L"{}h : {}m : {}s", hours, minutes, seconds);
		}
	}
}