#include "fepch.h"
#include "Application.h"
#include "Event/Event.h"
#include "GLFW/glfw3.h"
#include "Renderer/Renderer.h"

namespace FoxEngine
{

	Application* Application::s_Instance = nullptr;



	Application::Application()
	{
		FOX_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		FOX_CORE_DEBUG("Application was created.");
        m_WindowPtr = std::unique_ptr<Window>(Window::Create());
		m_WindowPtr->SetEventCallback(FOX_BIND_EVENT_FUNCTION(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}
	
	void Application::Run()
	{
		FOX_CORE_DEBUG("Application started.");
		while(Running)
		{
			float time = (float) glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			//Updating
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			
            m_WindowPtr->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) {
		EventCaster caster(event);
		caster.Cast<WindowClosedEvent>(FOX_BIND_EVENT_FUNCTION(Application::OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {

			(*--it)->OnEvent(event);
			if (event.IsHandled()) {
				break;
			}

		}
	}

	bool Application::OnWindowClosed(WindowClosedEvent& event) {
		Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

}

