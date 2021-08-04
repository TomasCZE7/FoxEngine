#include "fepch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace FoxEngine
{

	std::shared_ptr<spdlog::logger> Log::foxEngineLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;


	void Log::init()
	{
		spdlog::set_pattern("%^%T %l - %n: %v%$");

		foxEngineLogger = spdlog::stdout_color_mt("FOXENGINE");
		foxEngineLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("CLIENT");
		clientLogger->set_level(spdlog::level::trace);

		FOX_CORE_INFO("FoxEngine core log was initialized.");
        FOX_CLIENT_INFO("FoxEngine client log was initialized.");
	}

}
