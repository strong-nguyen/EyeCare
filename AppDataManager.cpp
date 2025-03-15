#include "pch.h"
#include "AppDataManager.h"

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
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path)))
	{
		std::wstring localapp_data_path = path;
		CoTaskMemFree(path);
		m_appdata_path = std::filesystem::path(localapp_data_path) / L"EyeCare";
		if (!std::filesystem::exists(m_appdata_path) && !std::filesystem::create_directory(m_appdata_path))
		{
			// TODO: Log cannot create app folder
		}
	}
	else
	{
		// TODO: Log
	}
}