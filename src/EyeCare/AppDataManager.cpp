#include "pch.h"
#include "AppDataManager.h"
#include <Logger.h>
#include "Common.h"

namespace fs = std::filesystem;


AppDataManager::AppDataManager()
{
	InitializeAppData();
}

AppDataManager* AppDataManager::GetInstance()
{
	static AppDataManager instance;
	return &instance;
}

fs::path AppDataManager::GetAppDataPath()
{
	return m_appdata_path;
}

void AppDataManager::InitializeAppData()
{
	PWSTR path = NULL;
	if (HRESULT ret = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path); SUCCEEDED(ret))
	{
		std::wstring localapp_data_path = path;
		CoTaskMemFree(path);
		m_appdata_path = std::filesystem::path(localapp_data_path) / L"EyeCare";
		std::error_code ec;
		if (!std::filesystem::exists(m_appdata_path) && !std::filesystem::create_directory(m_appdata_path, ec))
		{
			Common::OutputDebug(L"Failed to create appdata folder: %s, ec: %d", m_appdata_path.wstring().c_str(), ec.value());
		}
	}
	else
	{
		Common::OutputDebug(L"Failed to call SHGetKnownFolderPath, ret: %08X", ret);
	}
}