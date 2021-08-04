#include <FoxEngine.h>
#include <FoxEngine/Core/EntryPoint.h>

#include "imgui/imgui.h"
#include "FoxEngine/Renderer/Buffer.h"
#include "FoxEngine/Renderer/VertexArray.h"
#include "FoxEngine/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game2D.h"


class ExampleLayer : public FoxEngine::Layer {
	private:
		FoxEngine::OrthographicCameraController m_CameraController;
	
		FoxEngine::Ref<FoxEngine::Texture2D> m_Texture;

	public:
	FoxEngine::BufferLayout layout = {
		{FoxEngine::ShaderDataType::Float3, "a_Position"}
	};

	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		prepareTriangle();
	}

	void prepareTriangle()
	{
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		uint32_t indices[3] = { 0, 1, 2 };
	}


	~ExampleLayer()
	{
	}
	
	
	void onUpdate(FoxEngine::TimeStep timeStep){
		
	}

	void onEvent(FoxEngine::Event& event) {
        m_CameraController.onEvent(event);
	}

	virtual void onImGuiRender() override
	{

	}

};

class GameMain : public FoxEngine::Application
{

public:
	GameMain()
	{
		//pushLayer(new ExampleLayer());
        pushLayer(new Game2D());
	}
	~GameMain()
	{
		
	}
	
};

FoxEngine::Application* FoxEngine::createApplication()
{
	return new GameMain();
}