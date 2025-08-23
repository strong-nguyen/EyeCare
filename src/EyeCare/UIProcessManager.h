#pragma once
class UIProcessManager
{
public:
	static UIProcessManager* GetInstance();

	bool StartUIProcess();

	bool StopUIProcess();

private:
	UIProcessManager() = default;

	PROCESS_INFORMATION m_pi{};
};

