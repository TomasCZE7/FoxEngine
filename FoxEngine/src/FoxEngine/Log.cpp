#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Core.h"

namespace FoxEngine
{

	std::shared_ptr<spdlog::logger> Log::foxEngineLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;


	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		foxEngineLogger = spdlog::stdout_color_mt("FOXENGINE");
		foxEngineLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("CLIENT");
		clientLogger->set_level(spdlog::level::trace);
	}

}
