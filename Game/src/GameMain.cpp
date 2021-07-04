#include <FoxEngine.h>

class ExampleLayer : public FoxEngine::Layer {
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() {
	}

	void OnEvent(FoxEngine::Event& event) {
		FOX_CLIENT_DEBUG("Event {0}", event);
	}

};

class GameMain : public FoxEngine::Application
{

public:
	GameMain()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new FoxEngine::ImGuiLayer());
	}
	~GameMain()
	{
		
	}
	
};

FoxEngine::Application* FoxEngine::CreateApplication()
{
	return new GameMain();
}