#include "pch.h"

#include "Log.h"


std::shared_ptr<spdlog::logger> Log::s_Logger;


void Log::init(const char* name)
{
	// Names the logger
	s_Logger = spdlog::stdout_color_mt(name);
	// Sets the output pattern
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_Logger->set_level(spdlog::level::trace);

	LOG_INFO("Logger initialised.");
}
