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
        static void init();

        inline static std::shared_ptr<spdlog::logger> &GetFoxEngineLogger() { return foxEngineLogger; }

        inline static std::shared_ptr<spdlog::logger> &getClientLogger() { return clientLogger; }
    };
}
#define FOX_CORE_TRACE(...) ::FoxEngine::Log::GetFoxEngineLogger()->trace(__VA_ARGS__)
#define FOX_CORE_INFO(...) ::FoxEngine::Log::GetFoxEngineLogger()->info(__VA_ARGS__)
#define FOX_CORE_DEBUG(...) ::FoxEngine::Log::GetFoxEngineLogger()->debug(__VA_ARGS__)
#define FOX_CORE_ERROR(...) ::FoxEngine::Log::GetFoxEngineLogger()->error(__VA_ARGS__)
#define FOX_CORE_CRITICAL(...) ::FoxEngine::Log::GetFoxEngineLogger()->critical(__VA_ARGS__)

#define FOX_CLIENT_TRACE(...) ::FoxEngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define FOX_CLIENT_INFO(...) ::FoxEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define FOX_CLIENT_DEBUG(...) ::FoxEngine::Log::getClientLogger()->debug(__VA_ARGS__)
#define FOX_CLIENT_WARN(...) ::FoxEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define FOX_CLIENT_ERROR(...) ::FoxEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define FOX_CLIENT_CRITICAL(...) ::FoxEngine::Log::getClientLogger()->critical(__VA_ARGS__)