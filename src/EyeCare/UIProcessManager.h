#pragma once
class UIProcessManager
{
public:
	static UIProcessManager* GetInstance();

	~UIProcessManager();

	bool StartUIProcess();

	bool StopUIProcess();

private:
	UIProcessManager();

	bool InitJobObject();

	PROCESS_INFORMATION m_pi{};

	HANDLE m_job = nullptr;  // Job object to manage other process
};

