#ifndef LOGGER_HPP
#define LOGGER_HPP

//http://www.drdobbs.com/go-parallel/article/print?articleId=240147505&siteSectionName=

#include "log.hpp"

static logging::logger< logging::file_log_policy > log_inst( "execution.log" );

#ifdef LOGGING_LEVEL_1

#define LOG log_inst.print< logging::severity_type::debug >
#define LOG_ERR log_inst.print< logging::severity_type::error >
#define LOG_WARN log_inst.print< logging::severity_type::warning >

#else

//Preprocessor resolve, aka no logging
#define LOG(...) 
#define LOG_ERR(...)
#define LOG_WARN(...)

#endif

#ifdef LOGGING_LEVEL_2

#define ELOG log_inst.print< logging::severity_type::debug >
#define ELOG_ERR log_inst.print< logging::severity_type::error >
#define ELOG_WARN log_inst.print< logging::severity_type::warning >

#else

#define ELOG(...) 
#define ELOG_ERR(...)
#define ELOG_WARN(...)

#endif

#endif

/*
enum LogLevel{logBuffer, logError, logWarning, logInfo, logDebug, logTrace};
class Log{
public:
	Log();
	virtual ~Log();
	st::ostringstream& Get(LogLevel level= logInfo;
	
	static LogLevel& ReportingLevel();

private:

}
*/


////// Logger.hpp


////// Logger.cpp