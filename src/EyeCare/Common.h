#pragma once

#include <string>


// Common functions
namespace Common
{
	static LPCWSTR UI_PIPE_NAME = L"EyeCareUIPipe";

	static LPCWSTR PROCESS_JOB_OBJECT_NAME = L"EyeCareJob";

	static LPCWSTR UI_EXE_NAME = L"EyeCareUI.exe";

	std::wstring FormatTime(long seconds);

	template <typename ...Args>
	void OutputDebug(LPCWSTR msg, Args... args)
	{
		CStringW formatted_msg;
		formatted_msg.Format(msg, args...);
		OutputDebugStringW(formatted_msg.GetString());
	}
}