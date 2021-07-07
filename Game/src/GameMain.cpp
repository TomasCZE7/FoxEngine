#include <FoxEngine.h>

#include "imgui/imgui.h"
#include "FoxEngine/Renderer/Buffer.h"
#include "FoxEngine/Renderer/VertexArray.h"
#include "FoxEngine/Renderer/Renderer.h"

class ExampleLayer : public FoxEngine::Layer {
public:
	
	FoxEngine::BufferLayout layout = {
		{FoxEngine::ShaderDataType::Float3, "a_Position"},
		{FoxEngine::ShaderDataType::Float4, "a_Color"}
	};

	std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main(){
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}

		)";

	std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;
		
			in vec4 v_Color;
		
			void main(){
				o_Color = v_Color;
			}

		)";

	ExampleLayer()
		:Layer("Example")
	{
		prepareSquare();
		prepareTriangle();
	}

	void prepareTriangle()
	{
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0, 1.0f
		};
		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<FoxEngine::VertexArray> va = FoxEngine::VertexArray::Create();
		FoxEngine::Object* triangle = new FoxEngine::Object(va);
		triangle->AddVertexBuffer(vertices, sizeof(vertices), layout);
		triangle->SetIndexBuffer(indices, 3);

		triangle->SetShader(vertexSource, fragmentSource);
		AddObjects(triangle);
	}

	void prepareSquare()
	{
		float vertices[4 * 7] = {
			-0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.0, 1.0f,
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.0, 1.0f,
			0.75f, 0.75f, 0.0f, 1.0f, 0.0f, 0.0, 1.0f,
			-0.75f, 0.75f, 0.0f, 1.0f, 0.0f, 0.0, 1.0f
		};
		uint32_t indices[6] = { 0, 1, 2, 0, 3, 2 };

		std::shared_ptr<FoxEngine::VertexArray> va = FoxEngine::VertexArray::Create();
		FoxEngine::Object* square = new FoxEngine::Object(va);
		square->AddVertexBuffer(vertices, sizeof(vertices), layout);
		square->SetIndexBuffer(indices, 6);

		square->SetShader(vertexSource, fragmentSource);
		AddObjects(square);
	}

	~ExampleLayer()
	{
		for(auto object : Objects)
		{
			delete object;
		}
	}
	
	
	void OnUpdate() {
		FoxEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		FoxEngine::RenderCommand::Clear();

		FoxEngine::Renderer::BeginScene();
		
		RenderObjects();

		FoxEngine::Renderer::EndScene();
		
		
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