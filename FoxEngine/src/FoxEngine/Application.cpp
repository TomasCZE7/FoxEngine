#include "fepch.h"
#include "Application.h"
#include "Event/Event.h"

#include <glad/glad.h>

namespace FoxEngine
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FOX_ASSERT(!s_Instance, "Application already exists..!")
		s_Instance = this;

		FOX_CORE_DEBUG("Application was created.");
        m_WindowPtr = std::unique_ptr<Window>(Window::Create());
		m_WindowPtr->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
	}

	Application::~Application()
	{

	}
	
	void Application::Run()
	{
		FOX_CORE_DEBUG("Application started.");
		while(Running)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//Updating
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
            m_WindowPtr->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) {
		EventCaster caster(event);
		caster.Cast<WindowClosedEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClosed));

		FOX_CORE_TRACE("Event triggered: {0}", event);

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

