#pragma once
#include "Core.h"
#include <memory>
#include "spdlog/spdlog.h"

namespace FoxEngine
{
	class FE_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> foxEngineLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetFoxEngineLogger(){ return foxEngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){ return clientLogger; }
	};
}

#define FE_CORE_TRACE(...) ::FoxEngine::Log::GetFoxEngineLogger()->trace(__VA_ARGS__)
#define FE_CORE_INFO(...) ::FoxEngine::Log::GetFoxEngineLogger()->info(__VA_ARGS__)
#define FE_CORE_WARN(...) ::FoxEngine::Log::GetFoxEngineLogger()->warn(__VA_ARGS__)
#define FE_CORE_ERROR(...) ::FoxEngine::Log::GetFoxEngineLogger()->error(__VA_ARGS__)
#define FE_CORE_FATAL(...) ::FoxEngine::Log::GetFoxEngineLogger()->fatal(__VA_ARGS__)

#define FE_CLIENT_TRACE(...) ::FoxEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FE_CLIENT_INFO(...) ::FoxEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FE_CLIENT_WARN(...) ::FoxEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FE_CLIENT_ERROR(...) ::FoxEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FE_CLIENT_FATAL(...) ::FoxEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)