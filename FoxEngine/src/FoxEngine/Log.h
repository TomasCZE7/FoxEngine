#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace FoxEngine {
    class FOX_API Log {
    private:
        static std::shared_ptr<spdlog::logger> foxEngineLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetFoxEngineLogger() { return foxEngineLogger; }

        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return clientLogger; }
    };
}
#define FOX_CORE_TRACE(...) ::FoxEngine::Log::GetFoxEngineLogger()->trace(__VA_ARGS__)
#define FOX_CORE_INFO(...) ::FoxEngine::Log::GetFoxEngineLogger()->info(__VA_ARGS__)
#define FOX_CORE_DEBUG(...) ::FoxEngine::Log::GetFoxEngineLogger()->debug(__VA_ARGS__)
#define FOX_CORE_ERROR(...) ::FoxEngine::Log::GetFoxEngineLogger()->error(__VA_ARGS__)
#define FOX_CORE_CRITICAL(...) ::FoxEngine::Log::GetFoxEngineLogger()->critical(__VA_ARGS__)

#define FOX_CLIENT_TRACE(...) ::FoxEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FOX_CLIENT_INFO(...) ::FoxEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FOX_CLIENT_DEBUG(...) ::FoxEngine::Log::GetClientLogger()->debug(__VA_ARGS__)
#define FOX_CLIENT_WARN(...) ::FoxEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FOX_CLIENT_ERROR(...) ::FoxEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FOX_CLIENT_CRITICAL(...) ::FoxEngine::Log::GetClientLogger()->critical(__VA_ARGS__)