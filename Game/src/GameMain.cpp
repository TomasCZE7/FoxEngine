#include <FoxEngine.h>

#include "imgui/imgui.h"
#include "FoxEngine/Renderer/Buffer.h"
#include "FoxEngine/Renderer/VertexArray.h"
#include "FoxEngine/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public FoxEngine::Layer {
	private:
		FoxEngine::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraSpeed = 2.0f;
		float m_CameraRotationSpeed = 40.0f;
		float rotation = 0.0f;
		FoxEngine::Ref<FoxEngine::Object> triangle;
		FoxEngine::Ref<FoxEngine::Object> square;
	
		glm::vec4 squareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
		glm::vec4 triangleColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		FoxEngine::Ref<FoxEngine::Texture2D> m_Texture;

	public:
	FoxEngine::BufferLayout layout = {
		{FoxEngine::ShaderDataType::Float3, "a_Position"},
		{FoxEngine::ShaderDataType::Float2, "a_TextureCoord"}
	};

	ExampleLayer()
		: Layer("Example"), m_Camera( -1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({ 0.0f, 0.0f, 0.0f })
	{
		prepareSquare();
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
		
		triangle = std::make_shared<FoxEngine::Object>(FoxEngine::Object(FoxEngine::VertexArray::Create(), glm::vec3(0.0f)));
		triangle->AddVertexBuffer(vertices, sizeof(vertices), layout);
		triangle->SetIndexBuffer(indices, 3);

		triangle->SetShader("assets/shaders/Texture.glsl");
	}

	void prepareSquare()
	{
		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		};
		uint32_t indices[6] = { 0, 1, 2, 0, 3, 2 };
		
		square = std::make_shared<FoxEngine::Object>(FoxEngine::Object(FoxEngine::VertexArray::Create(), glm::vec3(0.0f)));
		square->AddVertexBuffer(vertices, sizeof(vertices), layout);
		square->SetIndexBuffer(indices, 6);

		square->SetShader("assets/shaders/Texture.glsl");

		m_Texture = FoxEngine::Texture2D::Create("assets/textures/minecraft_texture.png");
		square->GetShader()->UploadUniformInt("u_Texture", 0);
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

		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));

		//GRID
		square->GetShader()->Bind();
		square->GetShader()->UploadUniformFloat4("u_Color", squareColor);
		for(int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				FoxEngine::Renderer::Submit(square->GetVertexArray(), square->GetRawShader(), transform);
			}
		}
		
		m_Texture->Bind();
		FoxEngine::Renderer::Submit(square->GetVertexArray(), square->GetRawShader());

		//triangle->GetShader()->Bind();
		//triangle->GetShader()->UploadUniformFloat4("u_Color", triangleColor);
		//FoxEngine::Renderer::Submit(triangle->GetVertexArray(), triangle->GetRawShader(), triangle->GetTransform());

		FoxEngine::Renderer::EndScene();
		
		
	}

	void OnEvent(FoxEngine::Event& event) {
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Object settings");
		ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));
		//ImGui::ColorEdit4("Triangle color", glm::value_ptr(triangleColor));
		ImGui::End();
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