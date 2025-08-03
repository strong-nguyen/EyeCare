#pragma once


typedef void(*LoggerCallback)(const std::wstring& tag, const std::wstring& msg);

// PipeServer -> used in process that creates the Pipe
class __declspec(dllexport) PipeServer
{
public:
	PipeServer(const std::wstring& pipeName, LoggerCallback logger = nullptr);

	void Start();

private:
	void Log(const std::wstring& msg);

	std::wstring m_pipeName;

	LoggerCallback m_logger;
};

