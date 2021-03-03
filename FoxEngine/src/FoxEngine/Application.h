#pragma once
#include "Core.h"

namespace FoxEngine
{
	class FOX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}
