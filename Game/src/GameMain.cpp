#include <FoxEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public FoxEngine::Layer {
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() {
	}

	void OnEvent(FoxEngine::Event& event) {
	}

	virtual void OnImGuiRender() override
	{
	}

};

class GameMain : public FoxEngine::Application
{

public:
	GameMain()
	{
		PushLayer(new ExampleLayer());
	}
	~GameMain()
	{
		
	}
	
};

FoxEngine::Application* FoxEngine::CreateApplication()
{
	return new GameMain();
}