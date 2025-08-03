#pragma once

// PipeClient -> used in process that connects to the Pipe
class __declspec(dllexport) PipeClient
{
public:
	bool Connect(const std::wstring& pipeServerName);

	bool Notify(const std::string& message);

	~PipeClient();

private:
	HANDLE m_pipe = nullptr;
};

