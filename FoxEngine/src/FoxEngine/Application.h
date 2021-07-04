#pragma once
#include "Core.h"
#include "Window.h"
#include "Event/WindowEvent.h"
#include "FoxEngine/LayerStack.h"

namespace FoxEngine
{
	class FOX_API Application
	{
	private:
		bool Running = true;
		std::unique_ptr<Window> m_WindowPtr;
		LayerStack m_LayerStack;
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_WindowPtr;  }
		inline static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
		bool OnWindowClosed(WindowClosedEvent& event);
	};

	Application* CreateApplication();
}
