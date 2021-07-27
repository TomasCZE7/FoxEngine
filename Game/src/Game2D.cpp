#include "Game2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

Game2D::Game2D()
	: Layer("Game2D"), m_CameraController(1280.0f / 720.0f, true){
}

static const uint32_t s_MapWidth = 24;
static const uint32_t s_MapHeight = 11;

static const char* s_MapTiles =
"000000000000000000000000"
"000000000000000000000000"
"GGG000000000000000000000"
"DDDGG0000000C000000GGGGG"
"DDDDDGGG000GGG00GGGDDDDD"
"DDDDDDDDWWWWWWWWWDDDDDDD"
"DDDDDDDDDDWWWDDDDDDDDDDD"
"DDDDDDDDDDDDDDDDDDDDDDDD"
"DDDDDDDDDDDDDDDDDDDDDDDD"
"DDDDDDDDDDDDDDDDDDDDDDDD"
"DDDDDDDDDDDDDDDDDDDDDDDD"
;

void Game2D::OnAttach()
{
	m_MinecraftGrassTexture = FoxEngine::Texture2D::Create("assets/textures/minecraft_texture.png");
	m_SpriteSheet = FoxEngine::Texture2D::Create("assets/textures/platformer_tilemap.png");
	m_BackgroundSpriteSheet = FoxEngine::Texture2D::Create("assets/textures/background_tilemap.png");

	m_GrassTexture = FoxEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 8 }, { 18, 18 });
	m_DirtTexture = FoxEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 2 }, { 18, 18 });
	m_WaterTexture = FoxEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 13, 5 }, { 18, 18 });
	m_AirTexture = FoxEngine::SubTexture2D::CreateFromCoords(m_BackgroundSpriteSheet, { 0, 1 }, { 24, 24 });
	m_CoinTexture = FoxEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 1 }, { 18, 18 });
	m_CoinFlippedTexture = FoxEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 12, 1 }, { 18, 18 });


	s_TextureMap['0'] = m_AirTexture;
	s_TextureMap['G'] = m_GrassTexture;
	s_TextureMap['D'] = m_DirtTexture;
	s_TextureMap['W'] = m_WaterTexture;
	s_TextureMap['C'] = m_CoinTexture;

	FoxEngine::FrameBufferSpecification specification;
	specification.Width = 1280;
	specification.Height = 720;

	m_FrameBuffer = FoxEngine::FrameBuffer::Create(specification);
	
	m_CameraController.SetZoomLevel(5.0f);
}

void Game2D::OnDetach()
{
	
}

void Game2D::OnImGuiRender()
{

	static bool dockSpaceOpen = false;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            if (ImGui::MenuItem("Exit")) { FoxEngine::Application::Get().Shutdown(); }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

	ImGui::Begin("Renderer2D Statistics");

	auto stats = FoxEngine::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
	
	ImGui::Begin("Scene");
	uint32_t textureId = m_FrameBuffer->GetColorAttachmentRendererId();
	ImGui::Image((void*)textureId, ImVec2{ 1280.0f, 720.f });
	ImGui::End();

    ImGui::End();
}

void Game2D::OnEvent(FoxEngine::Event& event)
{
	m_CameraController.OnEvent(event);	
}

int32_t animation = 0;


void Game2D::OnUpdate(FoxEngine::TimeStep timeStep)
{
	if (animation > 0 && animation % 30 == 0)
	{
		animation = -30;
	}
	
	animation++;
	FOX_PROFILE_FUNCTION();
	FOX_CORE_DEBUG(timeStep.GetMilliseconds());

	m_CameraController.OnUpdate(timeStep);
	{
		FOX_PROFILE_SCOPE("Render preparation");
		m_FrameBuffer->Bind();
		FoxEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		FoxEngine::RenderCommand::Clear();
	}
	FoxEngine::Renderer2D::ResetStats();
		FoxEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		FOX_PROFILE_SCOPE("Render drawing");
		FoxEngine::Renderer2D::DrawQuad({ -1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
		FoxEngine::Renderer2D::DrawQuad({ -1.0f, 0.5f }, { 0.5f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		FoxEngine::Renderer2D::DrawQuad({ 0.0f, 0.5f, 0.1f }, { 0.5f, 0.8f }, m_MinecraftGrassTexture);
		FoxEngine::Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f }, { 0.8f, 0.8f }, glm::radians(84.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		FoxEngine::Renderer2D::DrawRotatedQuad({ 0.0f, -0.5f, 0.1f }, { 0.8f, 0.8f }, glm::radians(55.0f), m_MinecraftGrassTexture, { 0.2, 0.8, 0.3, 0.7 });
		FoxEngine::Renderer2D::DrawQuad({ 1.0f, 1.0f, 0.1f }, { 0.8f, 0.8f }, m_MinecraftGrassTexture, { 0.2, 0.3, 0.8, 0.9 }, 2.0f	);
	}

	FoxEngine::Renderer2D::EndScene();
	
	FoxEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
//	FoxEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f}, { 1.0f, 1.0f }, m_GrassTexture);
//	FoxEngine::Renderer2D::DrawQuad({ 1.0f, 0.0f}, { 1.0f, 1.0f }, m_DirtTexture);
//	FoxEngine::Renderer2D::DrawQuad({ 0.0f, 1.0f}, { 1.0f, 1.0f }, m_WaterTexture);
//	FoxEngine::Renderer2D::DrawQuad({ 1.0f, 1.0f}, { 1.0f, 1.0f }, m_AirTexture);

	for(uint32_t y = 0; y < s_MapHeight; y++)
	{
		for (uint32_t x = 0; x < s_MapWidth; x++)
		{
			char tile = s_MapTiles[x + y * s_MapWidth];
			FoxEngine::Ref<FoxEngine::SubTexture2D> subTexture;
			if(s_TextureMap.find(tile) != s_TextureMap.end())
			{
				subTexture = s_TextureMap[tile];
			}
			if(tile == 'C')
			{
				if(animation < 0)
				{
					subTexture = m_CoinFlippedTexture;
				}
				//FoxEngine::Renderer2D::DrawQuad({ s_MapWidth - x - s_MapWidth / 2.0f, s_MapHeight - y - s_MapHeight / 2.0f, 0.0f }, { 1.0f, 1.0f }, m_AirTexture);
			}
			//FoxEngine::Renderer2D::DrawQuad({ s_MapWidth - x - s_MapWidth / 2.0f, s_MapHeight - y - s_MapHeight / 2.0f, 0.5f}, { 1.0f, 1.0f }, subTexture);
		}
	}
	
	FoxEngine::Renderer2D::EndScene();
	m_FrameBuffer->Unbind();

}  
