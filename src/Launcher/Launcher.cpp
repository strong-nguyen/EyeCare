// Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>

int main()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	// Path to your executable
	LPCWSTR appPath = L"\"C:\\Program Files\\TakeABreak\\TakeABreak.exe\"";

	ShellExecuteW(
		NULL,                   // Parent window
		L"open",                 // Operation
		appPath, // File to open
		NULL,                   // Parameters
		NULL,                   // Default directory
		SW_SHOWNORMAL           // Window display option
	);

	return 0;
}

