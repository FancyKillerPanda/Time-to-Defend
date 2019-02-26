#pragma once

#include "pch.h"


class Log
{
private:
	static std::shared_ptr<spdlog::logger> s_Logger;

public:
	// Initialises the logger
	static void init();
	inline static std::shared_ptr<spdlog::logger>& getLogger() { return s_Logger; }
};


// Macros only defined when debugging symbols are on
#ifdef _DEBUG

#define LOG_TRACE(...)		Log::getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)		Log::getLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...)	Log::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		Log::getLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)		Log::getLogger()->critical(__VA_ARGS__)

#else

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)

#endif
