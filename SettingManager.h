#pragma once

#include <filesystem>
#include "EyeCareSetting.h"


class SettingManager
{
public:
	static SettingManager* GetInstance();

	void SaveSetting(const EyeCareSetting& setting);

	EyeCareSetting* GetSetting();

private:
	SettingManager();

	void LoadSetting();

	std::wstring ReadIniFile(LPCWSTR section, LPCWSTR key, LPCWSTR default_value);

	static std::filesystem::path config_path;

	EyeCareSetting m_setting;
};

