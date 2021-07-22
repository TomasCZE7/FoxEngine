#pragma once

#include "fepch.h"
#include "FoxEngine/Core/log.h"

#ifdef FOX_PLATFORM_WINDOWS

extern FoxEngine::Application* FoxEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		FoxEngine::Log::Init();

		FOX_PROFILE_BEGIN_SESSION("Startup", "FoxEngineProfile-StartupSession.json");
		auto app = FoxEngine::CreateApplication();
		FOX_PROFILE_END_SESSION();
		
		FOX_PROFILE_BEGIN_SESSION("Runtime", "FoxEngineProfile-RuntimeSession.json");
		app->Run();
		FOX_PROFILE_END_SESSION();
		
		FOX_PROFILE_BEGIN_SESSION("Shutdown", "FoxEngineProfile-ShutdownSession.json");
		delete app;
		FOX_PROFILE_END_SESSION();
	}

#endif