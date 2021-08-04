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
	class Application
	{
	private:
		bool running = true;
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		LayerStack layerStack;
		TimeStep timeStep;
		float lastFrameTime = 0.0f;
		bool minimized = false;
		
	public:
		Application(const std::string& name = "FoxEngine Application");
		virtual ~Application();

		void run();

		void onEvent(Event& event);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
		
		inline Window& getWindow() { return *window;  }
		inline static Application& getInstance() { return *instance; }
		inline ImGuiLayer* getImGuiLayer() { return imGuiLayer; }

		inline void shutdown() { running = false; }
	private:
		static Application* instance;
		bool onWindowClosed(WindowClosedEvent& event);
		bool onWindowResized(WindowResizedEvent& event);
	};

	Application* createApplication();
}
