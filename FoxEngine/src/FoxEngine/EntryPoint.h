#pragma once
#ifdef FE_PLATFORM_WINDOWS

extern FoxEngine::Application* FoxEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		auto app = FoxEngine::CreateApplication();
		app->Run();
		delete app;
	}

#endif