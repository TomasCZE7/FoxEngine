#include "Game2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

Game2D::Game2D()
	: Layer("Game2D"), m_CameraController(1280.0f / 720.0f){
}

void Game2D::OnAttach()
{
	m_VertexArray = FoxEngine::VertexArray::Create();
	float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};
	
	FoxEngine::BufferLayout layout = {
		{FoxEngine::ShaderDataType::Float3, "a_Position"},
	};

	FoxEngine::Ref<FoxEngine::VertexBuffer> vertexBuffer = FoxEngine::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout(layout);

	m_VertexArray->AddVertexBuffer(vertexBuffer);
	
	uint32_t indices[6] = { 0, 1, 2, 0, 3, 2 };
	
	FoxEngine::Ref<FoxEngine::IndexBuffer> indexBuffer = FoxEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	m_VertexArray->SetIndexBuffer(indexBuffer);
	m_Shader = FoxEngine::Shader::Create("assets/shaders/FlatColor.glsl");
	
	
}

void Game2D::OnDetach()
{
	
}

void Game2D::OnImGuiRender()
{
	ImGui::Begin("Scene settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_Color));
	ImGui::End();
}

void Game2D::OnEvent(FoxEngine::Event& event)
{
	m_CameraController.OnEvent(event);	
}

void Game2D::OnUpdate(FoxEngine::TimeStep timeStep)
{
	m_CameraController.OnUpdate(timeStep);

	FoxEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	FoxEngine::RenderCommand::Clear();

	FoxEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	FoxEngine::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.2f, 0.8f, 0.3f, 1.0f});
	FoxEngine::Renderer2D::DrawQuad({-1.0f, 0.5f}, {0.5f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0f});

	FoxEngine::Renderer2D::EndScene();
}
