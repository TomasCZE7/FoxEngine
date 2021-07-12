#pragma once

#include "fepch.h"
#include "FoxEngine/Core/log.h"

#ifdef FOX_PLATFORM_WINDOWS

extern FoxEngine::Application* FoxEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		FoxEngine::Log::Init();
		auto app = FoxEngine::CreateApplication();
		app->Run();
		delete app;
	}

#endif