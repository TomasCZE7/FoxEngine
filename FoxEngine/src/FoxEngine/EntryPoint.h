#pragma once
#ifdef FE_PLATFORM_WINDOWS

extern FoxEngine::Application* FoxEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		FoxEngine::Log::Init();
		auto app = FoxEngine::CreateApplication();
		app->Run();
		delete app;
	}

#endif