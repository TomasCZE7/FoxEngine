#pragma once
#include "FoxEngine/Core/Core.h"
#include "FoxEngine/Core/Layer.h"
#include "FoxEngine/Core/Window.h"
#include "FoxEngine/Core/TimeStep.h"
#include "FoxEngine/Event/WindowEvent.h"
#include "FoxEngine/Core/LayerStack.h"
#include "FoxEngine/ImGui/ImGuiLayer.h"
#include "FoxEngine/Renderer/OrthographicCamera.h"
#include "FoxEngine/Renderer/VertexArray.h"

namespace FoxEngine
{
	class FOX_API Application
	{
	private:
		bool Running = true;
		std::unique_ptr<Window> m_WindowPtr;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		TimeStep m_TimeStep;
		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;
		
	public:
		Application(const std::string& name = "FoxEngine Application");
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		inline Window& GetWindow() { return *m_WindowPtr;  }
		inline static Application& Get() { return *s_Instance; }
		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline void Shutdown() { Running = false; }
	private:
		static Application* s_Instance;
		bool OnWindowClosed(WindowClosedEvent& event);
		bool OnWindowResized(WindowResizedEvent& event);
	};

	Application* CreateApplication();
}
