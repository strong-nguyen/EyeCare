#pragma once


typedef void(*LoggerCallback)(const std::wstring& tag, const std::wstring& msg);

class __declspec(dllexport)IPipe
{
public:
	virtual ~IPipe() = default;

	static void SetLoggerInterface(LoggerCallback logger);

protected:
	void Log(const std::wstring& msg);

private:

	inline static LoggerCallback _logger = nullptr;
};

