#include "Game2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

Game2D::Game2D()
	: Layer("Game2D"), m_CameraController(1280.0f / 720.0f, true){
}

void Game2D::OnAttach()
{
	m_MinecraftGrassTexture = FoxEngine::Texture2D::Create("assets/textures/minecraft_texture.png");
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
	FOX_PROFILE_FUNCTION();
	m_CameraController.OnUpdate(timeStep);
	{
		FOX_PROFILE_SCOPE("Render preparation");
		FoxEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		FoxEngine::RenderCommand::Clear();
	}
	FoxEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		FOX_PROFILE_SCOPE("Render drawing");
		FoxEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
		FoxEngine::Renderer2D::DrawQuad({ -1.0f, 0.5f }, { 0.5f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	//	FoxEngine::Renderer2D::DrawQuad({ 0.0f, 0.5f, 0.1f }, { 0.5f, 0.8f }, m_MinecraftGrassTexture);
		//FoxEngine::Renderer2D::DrawRotatedQuad({ 0.0f, -0.5f, 0.1f }, { 0.8f, 0.8f }, glm::radians(55.0f), m_MinecraftGrassTexture, { 0.2, 0.8, 0.3, 0.7 });
		//FoxEngine::Renderer2D::DrawQuad({ 1.0f, 1.0f, 0.1f }, { 0.8f, 0.8f }, m_MinecraftGrassTexture, { 0.2, 0.3, 0.8, 0.9 });
	}

	FoxEngine::Renderer2D::EndScene();
}  
