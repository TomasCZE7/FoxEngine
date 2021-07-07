#include <FoxEngine.h>

#include "imgui/imgui.h"
#include "FoxEngine/Renderer/Buffer.h"
#include "FoxEngine/Renderer/VertexArray.h"
#include "FoxEngine/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public FoxEngine::Layer {
	private:
		FoxEngine::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraSpeed = 2.0f;
		float m_CameraRotationSpeed = 40.0f;
		float rotation = 0.0f;
		FoxEngine::Object triangle;
		FoxEngine::Object square;

	public:
	FoxEngine::BufferLayout layout = {
		{FoxEngine::ShaderDataType::Float3, "a_Position"},
		{FoxEngine::ShaderDataType::Float4, "a_Color"}
	};
	 
	std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 m_ViewProjection;
			uniform mat4 m_Transform;
	
			out vec4 v_Color;

			void main(){
				v_Color = a_Color;
				gl_Position = m_ViewProjection * m_Transform * vec4(a_Position, 1.0);
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
		: Layer("Example"), m_Camera( -1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({ 0.0f, 0.0f, 0.0f })
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
		
		triangle = FoxEngine::Object(FoxEngine::VertexArray::Create(), glm::vec3(0.0f));
		triangle.AddVertexBuffer(vertices, sizeof(vertices), layout);
		triangle.SetIndexBuffer(indices, 3);

		triangle.SetShader(vertexSource, fragmentSource);
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
		
		square = FoxEngine::Object(FoxEngine::VertexArray::Create(), glm::vec3(0.0f));
		square.AddVertexBuffer(vertices, sizeof(vertices), layout);
		square.SetIndexBuffer(indices, 6);

		square.SetShader(vertexSource, fragmentSource);

	}

	~ExampleLayer()
	{
	}
	
	
	void OnUpdate(FoxEngine::TimeStep timeStep) {
		
		if (FoxEngine::Input::IsKeyPressed(FOX_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed * timeStep;
		}
		if (FoxEngine::Input::IsKeyPressed(FOX_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed * timeStep;
		}
		if (FoxEngine::Input::IsKeyPressed(FOX_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed * timeStep;
		}
		if (FoxEngine::Input::IsKeyPressed(FOX_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed * timeStep;
		}

		if (FoxEngine::Input::IsKeyPressed(FOX_KEY_E))
		{
			rotation += m_CameraRotationSpeed * timeStep;
		}

		if (FoxEngine::Input::IsKeyPressed(FOX_KEY_Q))
		{
			rotation -= m_CameraRotationSpeed * timeStep;
		}

		FoxEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		FoxEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(rotation);
		
		FoxEngine::Renderer::BeginScene(m_Camera);

		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.07));

		//GRID
		for(int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				FoxEngine::Renderer::Submit(square.GetVertexArray(), square.GetShader(), transform);
			}
		}
		
		FoxEngine::Renderer::Submit(triangle.GetVertexArray(), triangle.GetShader(), triangle.GetTransform());

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