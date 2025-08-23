#pragma once

#include <filesystem>


/*
* Manage the local appdata folder of EyeCare
*/
class AppDataManager
{
public:
	static AppDataManager* GetInstance();

	std::filesystem::path GetAppDataPath();

private:
	AppDataManager();

	void InitializeAppData();

	std::filesystem::path m_appdata_path;
};

