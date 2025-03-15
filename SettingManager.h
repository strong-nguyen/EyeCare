#pragma once

#include "EyeCareSetting.h"
#include <filesystem>


class SettingManager
{
public:
	static SettingManager* GetInstance();

	void LoadSetting(EyeCareSetting& setting);

	void SaveSetting(const EyeCareSetting& setting);

private:
	SettingManager() = default;

	std::wstring ReadIniFile(LPCWSTR section, LPCWSTR key, LPCWSTR default_value);

	static std::filesystem::path config_path;
};

