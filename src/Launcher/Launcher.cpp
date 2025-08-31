// Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <shobjidl.h>     // IShellLink
#include <shlobj.h>
#include <strsafe.h>
#include <filesystem>

static LPCWSTR TakeABreakExePath = L"C:\\Program Files\\TakeABreak\\TakeABreak.exe";

bool CreateShortcut(const wchar_t* targetPath, const wchar_t* shortcutPath, const wchar_t* description, const wchar_t* iconPath) {
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) return false;

	std::filesystem::path workingDir = std::filesystem::path(targetPath).parent_path();

	IShellLinkW* pShellLink = nullptr;
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&pShellLink);
	if (SUCCEEDED(hr)) {
		pShellLink->SetPath(targetPath);
		pShellLink->SetDescription(description);
		pShellLink->SetIconLocation(iconPath, 0);
		pShellLink->SetWorkingDirectory(workingDir.wstring().c_str());

		IPersistFile* pPersistFile;
		hr = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);
		if (SUCCEEDED(hr)) {
			hr = pPersistFile->Save(shortcutPath, TRUE);
			pPersistFile->Release();
		}
		pShellLink->Release();
	}

	CoUninitialize();
	return SUCCEEDED(hr);
}

void LaunchTakeABreak()
{
	STARTUPINFO si = {};
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;

	LPCWSTR appPath = L"\"C:\\Program Files\\TakeABreak\\TakeABreak.exe\"";

	ShellExecuteW(
		NULL,                   // Parent window
		L"open",                 // Operation
		appPath, // File to open
		NULL,                   // Parameters
		NULL,                   // Default directory
		SW_SHOWNORMAL           // Window display option
	);
}

int main()
{
	wchar_t desktopPath[MAX_PATH] = {};
	wchar_t startMenuPath[MAX_PATH] = {};

	SHGetSpecialFolderPathW(NULL, desktopPath, CSIDL_DESKTOP, FALSE);
	SHGetSpecialFolderPathW(NULL, startMenuPath, CSIDL_PROGRAMS, FALSE);  // Start Menu\Programs

	wchar_t desktopShortcut[MAX_PATH] = {};
	StringCchPrintfW(desktopShortcut, MAX_PATH, L"%s\\Take A Break.lnk", desktopPath);

	wchar_t startMenuShortcut[MAX_PATH];
	StringCchPrintfW(startMenuShortcut, MAX_PATH, L"%s\\Take A Break.lnk", startMenuPath);

	CreateShortcut(TakeABreakExePath, desktopShortcut, L"Launch Take A Break application", TakeABreakExePath);
	CreateShortcut(TakeABreakExePath, startMenuShortcut, L"Launch Take A Break application", TakeABreakExePath);

	LaunchTakeABreak();

	return 0;
}

