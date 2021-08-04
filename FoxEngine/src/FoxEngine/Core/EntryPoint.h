#pragma once

#include "fepch.h"
#include "FoxEngine/Core/log.h"

#ifdef FOX_PLATFORM_WINDOWS

extern FoxEngine::Application* FoxEngine::createApplication();

	int main(int argc, char** argv)
	{
        FoxEngine::Log::init();

        FOX_PROFILE_BEGIN_SESSION("Startup", "FoxEngineProfile-StartupSession.json");
		auto app = FoxEngine::createApplication();
        FOX_PROFILE_END_SESSION();

        FOX_PROFILE_BEGIN_SESSION("Runtime", "FoxEngineProfile-RuntimeSession.json");
        app->run();
        FOX_PROFILE_END_SESSION();

        FOX_PROFILE_BEGIN_SESSION("shutdown", "FoxEngineProfile-ShutdownSession.json");
		delete app;
        FOX_PROFILE_END_SESSION();
	}

#endif