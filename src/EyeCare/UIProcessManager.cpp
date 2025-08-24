#include "pch.h"
#include "UIProcessManager.h"
#include <PipeClient.h>
#include <format>
#include <filesystem>
#include <Logger.h>


UIProcessManager* UIProcessManager::GetInstance()
{
	static UIProcessManager instance;
	return &instance;
}

UIProcessManager::UIProcessManager()
{
	InitJobObject();
}

UIProcessManager::~UIProcessManager()
{
	::CloseHandle(m_job);
	m_job = nullptr;
}

bool UIProcessManager::InitJobObject()
{
	m_job = ::CreateJobObject(nullptr, L"EyeCareJob");
	if (m_job == nullptr)
	{
		CommonLib::log(L"UI").Error(L"CreateJobObject failed, ec: %d", ::GetLastError());
		return false;
	}

	JOBOBJECT_EXTENDED_LIMIT_INFORMATION job_info = {};
	job_info.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	if (!::SetInformationJobObject(m_job, JobObjectExtendedLimitInformation, &job_info, sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION)))
	{
		CommonLib::log(L"UI").Error(L"SetInformationJobObject failed, ec: %d", ::GetLastError());
		return false;
	}

	return true;
}

bool UIProcessManager::StartUIProcess()
{
#ifdef _DEBUG
	TCHAR exe_path[MAX_PATH] = {};
	DWORD length = GetModuleFileName(NULL, exe_path, MAX_PATH);
	LPCWSTR process_name = L"..\\EyeCareUI\\bin\\Debug\\net8.0-windows\\EyeCareUI.exe";
	std::filesystem::path ui_exe_path;
	if (length > 0)
	{
		ui_exe_path = exe_path;
		for (int i = 0; i < 4; ++i)
		{
			ui_exe_path /= "..";
		};
		ui_exe_path = ui_exe_path / "EyeCareUI\\bin\\Debug\\net8.0-windows\\EyeCareUI.exe";

		process_name = ui_exe_path.c_str();
	}
	else
	{
		CommonLib::log(L"UI").Error(L"GetModuleFileName failed");
	}
#else
	LPCWSTR process_name = L"EyeCareUI.exe";
#endif

	STARTUPINFO start_info{};
	start_info.cb = sizeof(STARTUPINFO);

	BOOL ret = ::CreateProcessW(
		process_name,
		nullptr,
		nullptr,
		nullptr,
		FALSE,
		0,
		nullptr,
		nullptr,
		&start_info,
		&m_pi
	);

	if (!ret)
	{
		CommonLib::log(L"UI").Error(L"CreateProcess failed, ec: %d", ::GetLastError());
		return false;
	}

	if (!::AssignProcessToJobObject(m_job, m_pi.hProcess))
	{
		CommonLib::log(L"UI").Error(L"AssignProcessToJobObject failed, ec: %d", ::GetLastError());
		return false;
	}

	return true;
}

bool UIProcessManager::StopUIProcess()
{
	bool ret = true;
	if (m_pi.hProcess)
	{
		bool is_ui_process_quit = false;
		do
		{
			PipeClient client;
			if (!client.Connect(L"EyeCareUIPipe"))
			{
				break;
			}

			if (!client.Notify("quit"))
			{
				break;
			}

			DWORD wait_ret = ::WaitForSingleObject(m_pi.hProcess, 2'000);
			if (wait_ret == WAIT_OBJECT_0)
			{
				// Process already quit/ quit in 2s
				is_ui_process_quit = true;
			}

		} while (false);

		if (!is_ui_process_quit)
		{
			ret = TerminateProcess(m_pi.hProcess, 0);
		}
		::CloseHandle(m_pi.hProcess);
	}

	if (m_pi.hThread)
	{
		::CloseHandle(m_pi.hThread);
	}

	return ret;
}
