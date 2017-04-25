#include "Core/include/Core.hpp"


class LoggerManager
{
	friend class Logger;

public:
	LoggerManager() = default;
	~LoggerManager() = default;

	Core::Logger* logger = nullptr;
};


LoggerManager gLoggerMgr;


Core::Logger::Logger()
	: mLogLevel(LDEFAULT)
{
}


auto	Core::Logger::LogLevel() -> ELOG_TYPE
{
	return gLoggerMgr.logger->mLogLevel;
}


auto	Core::Logger::SetLogLevel(ELOG_TYPE logLevel) -> void
{
	gLoggerMgr.logger->mLogLevel = logLevel;
}


auto	Core::Logger::Initialize() -> void
{
	gLoggerMgr.logger = new Logger();
}


auto	Core::Logger::Shutdown() -> void
{
	delete gLoggerMgr.logger;
}


auto	Core::Logger::RegisterOutputCallback(const std::function<void(const string&)>& outputCallback) -> void
{
	gLoggerMgr.logger->mOutputCallbacks.push_back(outputCallback);
}


auto	Core::Logger::Log(const string& logMessage, ELOG_TYPE logType) -> void
{
	if (logType >= gLoggerMgr.logger->mLogLevel)
	{
		for (auto output : gLoggerMgr.logger->mOutputCallbacks)
		{
			output(logMessage);
		}
	}
}


/*auto 	Core::Log(const string& logMessage, Logger::ELOG_TYPE logType) -> void
{
	Core::Logger::Log(logMessage, logType);
}*/