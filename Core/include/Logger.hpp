#pragma once


#define FIRST_PREFIX	string("")

#define VERBOSE_PREFIX	string("[VERBOSE]")
#define INFO_PREFIX		string("[INFO]")
#define DEBUG_PREFIX	string("[DEBUG]")
#define WARNING_PREFIX	string("[WARNING]")
#define ERROR_PREFIX	string("[ERROR]")
#define CRITICAL_PREFIX	string("[CRITICAL]")
#define DEFAULT_PREFIX	DEBUG_PREFIX

#define ADDITIONAL_PREFIX string("")

#define FILEPATH	string(__FILE__)
#define RFILEPATH	string(strstr(__FILE__, "src") ? strstr(__FILE__, "src") : strstr(__FILE__, "include"))
#define FUNC		string(__FUNCTION__)
#define LINE		string(std::to_string(__LINE__))

#define FULL_LOG_DESC (string("\n(") + FUNC + " \"" + FILEPATH + ":" + LINE + string("\")"))
#define LOG_DESC (string("\n(") + FUNC + " \"" + RFILEPATH + ":" + LINE + string("\")"))
#define LOW_LOG_DESC (string("\n(") + " \"" + RFILEPATH + ":" + LINE + string("\")"))

using OutputCallback = std::function<void(const string&)>;

class CORE_EXTERNAL Logger
{
public:
	enum ELOG_TYPE
	{
		LVERBOSE = 0,
		LINFO,
		LDEBUG,
		LWARNING,
		LERROR,
		LCRITICAL,
		LDEFAULT = LDEBUG
	};

	static auto LogLevel() -> ELOG_TYPE;
	static auto	SetLogLevel(ELOG_TYPE logLevel) -> void;

	static auto	Initialize() -> void;
	static auto	Shutdown() -> void;

	static auto	RegisterOutputCallback(const std::function<void(const string&)>& outputCallback) -> void;

	static auto	Log(const string& logMessage, ELOG_TYPE logType = LDEFAULT) -> void;

private:
	Logger();

	vector<OutputCallback>	mOutputCallbacks;
	ELOG_TYPE				mLogLevel;
};


#define LOG_VERSBOSE(log)	Core::Logger::Log(FIRST_PREFIX + VERBOSE_PREFIX + ADDITIONAL_PREFIX + " " + log + LOG_DESC, Core::Logger::ELOG_TYPE::LVERBOSE);
#define LOG_INFO(log)		Core::Logger::Log(FIRST_PREFIX + INFO_PREFIX + ADDITIONAL_PREFIX + " " + log + LOG_DESC, Core::Logger::ELOG_TYPE::LINFO);
#define LOG_DEBUG(log)		Core::Logger::Log(FIRST_PREFIX + DEBUG_PREFIX + ADDITIONAL_PREFIX + " " + log + LOG_DESC, Core::Logger::ELOG_TYPE::LDEBUG);
#define LOG_WARNING(log)	Core::Logger::Log(FIRST_PREFIX + WARNING_PREFIX + ADDITIONAL_PREFIX + " " + log + LOG_DESC, Core::Logger::ELOG_TYPE::LWARNING);
#define LOG_ERROR(log)		Core::Logger::Log(FIRST_PREFIX + ERROR_PREFIX + ADDITIONAL_PREFIX + " " + log + LOG_DESC, Core::Logger::ELOG_TYPE::LERROR);
#define LOG_CRITICAL(log)	Core::Logger::Log(FIRST_PREFIX + CRITICAL_PREFIX + ADDITIONAL_PREFIX + " " + log + LOG_DESC, Core::Logger::ELOG_TYPE::LCRITICAL);
#define LOG(log)			Core::Logger::Log(FIRST_PREFIX + DEFAULT_PREFIX + ADDITIONAL_PREFIX + " " + log + LOG_DESC, Core::Logger::ELOG_TYPE::LDEFAULT);
