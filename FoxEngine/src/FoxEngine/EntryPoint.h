#pragma once
#ifdef FOX_PLATFORM_WINDOWS

extern FoxEngine::Application* FoxEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		FoxEngine::Log::Init();
        FOX_CORE_INFO("FoxEngine core log was initialized.");
        FOX_CLIENT_INFO("FoxEngine client log was initialized.");
		auto app = FoxEngine::CreateApplication();
		app->Run();
		delete app;
	}

#endif