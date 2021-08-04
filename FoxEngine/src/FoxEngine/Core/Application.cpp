#include "fepch.h"
#include "Application.h"
#include "FoxEngine/Event/Event.h"
#include "GLFW/glfw3.h"
#include "FoxEngine/Renderer/Renderer.h"

#include <iostream>
#include <filesystem>

namespace FoxEngine
{

	Application* Application::instance = nullptr;

	Application::Application(const std::string& name)
	{
		FOX_ASSERT(!instance, "Application already exists!")
		instance = this;

		FOX_CORE_DEBUG("Application was created.");
        window = std::unique_ptr<Window>(Window::create(WindowProperties(name)));
        window->setEventCallback(FOX_BIND_EVENT_FUNCTION(Application::onEvent));

        Renderer::init();

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
	}

	Application::~Application()
	{

	}
	
	void Application::run()
	{
		FOX_CORE_DEBUG("Application started.");
		while(running)
		{
			float time = (float) glfwGetTime();
			TimeStep timestep = time - lastFrameTime;
            lastFrameTime = time;
			//Updating
			if (!minimized) {
				for (Layer* layer : layerStack) {
                    layer->onUpdate(timestep);
				}
			}

            imGuiLayer->begin();
			for (Layer* layer : layerStack) {
                layer->onImGuiRender();
			}
            imGuiLayer->end();


            window->onUpdate();
		}
	}

	void Application::onEvent(Event& event) {
		EventCaster caster(event);
        caster.cast<WindowClosedEvent>(FOX_BIND_EVENT_FUNCTION(Application::onWindowClosed));
        caster.cast<WindowResizedEvent>(FOX_BIND_EVENT_FUNCTION(Application::onWindowResized));

		for (auto it = layerStack.end(); it != layerStack.begin();) {

            (*--it)->onEvent(event);
			if (event.isHandled()) {
				break;
			}

		}
	}

	bool Application::onWindowClosed(WindowClosedEvent& event) {
        running = false;
		return true;
	}

	bool Application::onWindowResized(WindowResizedEvent& event)
	{
		if(event.getWidth() == 0 || event.getHeight() == 0)
		{
            minimized = true;
			return false;
		}

        minimized = false;
        Renderer::onWindowResized(event.getWidth(), event.getHeight());
		return false;
	}

	void Application::pushLayer(Layer* layer) {
        layerStack.pushLayer(layer);
        layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer) {
        layerStack.pushOverlay(layer);
        layer->onAttach();
	}

}

