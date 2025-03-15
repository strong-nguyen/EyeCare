#pragma once

#include <filesystem>


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

