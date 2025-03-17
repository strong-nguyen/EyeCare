#include "pch.h"
#include "SettingManager.h"
#include "AppDataManager.h"
#include <fstream>


std::filesystem::path SettingManager::config_path = AppDataManager::GetInstance()->GetAppDataPath() / L"config.ini";

SettingManager::SettingManager()
{
	LoadSetting();
}

SettingManager* SettingManager::GetInstance()
{
	static SettingManager instance;
	return &instance;
}

void SettingManager::LoadSetting()
{
	std::wstring break_time = ReadIniFile(L"AppConfig", L"BreakTimeMs", L"3000000");
	std::wstring relax_time = ReadIniFile(L"AppConfig", L"RelaxTimeMs", L"600000");
	std::wstring is_auto_start = ReadIniFile(L"AppConfig", L"IsAutoStart", L"1");
	EyeCareSetting config_setting(std::stol(break_time) / (1000.0f * 60), std::stol(relax_time) / (1000.0f * 60), is_auto_start == L"1");
	m_setting = config_setting;
}

void SettingManager::SaveSetting(const EyeCareSetting& setting)
{
	m_setting = setting;

	std::wofstream config_file(config_path, std::ios_base::out | std::ios_base::trunc);
	config_file << L"[AppConfig]\n";
	config_file << L"BreakTimeMs=" << setting.GetBreakTimeMilliSecond() << L"\n";
	config_file << L"RelaxTimeMs=" << setting.GetRelaxTimeMilliSecond() << L"\n";
	config_file << L"IsAutoStart=" << (int)setting.IsAutoStart() << L"\n";
}

EyeCareSetting* SettingManager::GetSetting()
{
	return &m_setting;
}

std::wstring SettingManager::ReadIniFile(LPCWSTR section, LPCWSTR key, LPCWSTR default_value)
{
	if (section == nullptr || key == nullptr)
	{
		return default_value;
	}

	if (!std::filesystem::exists(config_path))
	{
		return default_value;
	}
	wchar_t* buffer = new wchar_t[100] {};
	std::wstring config_file_path = config_path.wstring();
	GetPrivateProfileStringW(section, key, default_value, buffer, 100, config_file_path.c_str());
	return buffer;
}
