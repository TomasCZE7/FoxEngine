#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>

#include "imgui/imgui.h"

namespace FoxEngine
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true) {
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

	void EditorLayer::OnAttach()
	{
		m_MinecraftGrassTexture = Texture2D::Create("assets/textures/minecraft_texture.png");
		m_SpriteSheet = Texture2D::Create("assets/textures/platformer_tilemap.png");
		m_BackgroundSpriteSheet = Texture2D::Create("assets/textures/background_tilemap.png");

		m_GrassTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 8 }, { 18, 18 });
		m_DirtTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 2 }, { 18, 18 });
		m_WaterTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 13, 5 }, { 18, 18 });
		m_AirTexture = SubTexture2D::CreateFromCoords(m_BackgroundSpriteSheet, { 0, 1 }, { 24, 24 });
		m_CoinTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 1 }, { 18, 18 });
		m_CoinFlippedTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 12, 1 }, { 18, 18 });


		s_TextureMap['0'] = m_AirTexture;
		s_TextureMap['G'] = m_GrassTexture;
		s_TextureMap['D'] = m_DirtTexture;
		s_TextureMap['W'] = m_WaterTexture;
		s_TextureMap['C'] = m_CoinTexture;

		FrameBufferSpecification specification;
		specification.Width = 1280;
		specification.Height = 720;

		m_FrameBuffer = FrameBuffer::Create(specification);

		m_CameraController.SetZoomLevel(5.0f);
	}

	void EditorLayer::OnDetach()
	{

	}


	bool stopGraph = false;
	void EditorLayer::OnImGuiRender()
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
				if (ImGui::MenuItem("Exit")) { Application::Get().Shutdown(); }

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Renderer2D Statistics");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::End();

		ImGui::Begin("Renderer performance");
		float* p = &m_TimeSteps[0];
		ImVec2 performanceSize = ImGui::GetContentRegionAvail();
		if(m_CameraController.GetMouseState() == MouseState::MOVING_CAMERA)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
		} else
		{
		//	ImGui::SetMouseCursor();
		}
		//ImGui::GetForegroundDrawList()->AddImage((void*)m_MinecraftGrassTexture->GetRendererId(), { io.MousePos.x - 25 , io.MousePos.y - 25 }, { io.MousePos.x + 25 , io.MousePos.y + 25 }, {0,1}, {1, 0});
		ImGui::PlotLines("Framerate (ms)", p, m_TimeSteps.size(), 0, 0, 0, 100, ImVec2{ performanceSize.x, 128 });
		if(ImGui::Button("Toggle pause"))
		{
			stopGraph = !stopGraph;
		}

		ImGui::SliderInt("TimeStep count", &m_TimeStepsMaxCount, 2, 1000);
		
		std::string framerate = "Framerate: " + std::to_string(m_TimeSteps[m_TimeSteps.size() - 1]) + " ms";
		
		ImGui::Text(framerate.c_str());
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Scene");
		m_ViewPortFocused = ImGui::IsWindowFocused();
		m_ViewPortHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewPortFocused || !m_ViewPortHovered);

		ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
		if(m_ViewPortSize != *((glm::vec2*)&viewPortSize))
		{
			m_ViewPortSize = { viewPortSize.x, viewPortSize.y };
			m_FrameBuffer->Resize((uint32_t)m_ViewPortSize.x, (uint32_t)m_ViewPortSize.y);
			m_CameraController.OnResize(m_ViewPortSize.x, m_ViewPortSize.y);
		}
		uint32_t textureId = m_FrameBuffer->GetColorAttachmentRendererId();
		ImGui::Image((void*)textureId, { m_ViewPortSize.x, m_ViewPortSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
		ImGui::End();
		ImGui::PopStyleVar();
		
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);
	}


	int32_t animation = 0; //todo
	void EditorLayer::OnUpdate(TimeStep timeStep)
	{
		if (animation > 0 && animation % 30 == 0)
		{
			animation = -30;
		}
		
		animation++;
		FOX_PROFILE_FUNCTION();
		if(m_ViewPortFocused && m_ViewPortHovered)
			m_CameraController.OnUpdate(timeStep);
		{
			FOX_PROFILE_SCOPE("Render preparation");
			m_FrameBuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
		}
		Renderer2D::ResetStats();

		Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (uint32_t y = 0; y < s_MapHeight; y++)
		{
			for (uint32_t x = 0; x < s_MapWidth; x++)
			{
				char tile = s_MapTiles[x + y * s_MapWidth];
				Ref<SubTexture2D> subTexture;
				if (s_TextureMap.find(tile) != s_TextureMap.end())
				{
					subTexture = s_TextureMap[tile];
				}
				if (tile == 'C')
				{
					if (animation < 0)
					{
						subTexture = m_CoinFlippedTexture;
					}
					Renderer2D::DrawQuad({ s_MapWidth - x - s_MapWidth / 2.0f, s_MapHeight - y - s_MapHeight / 2.0f, 0.0f }, { 1.0f, 1.0f }, m_AirTexture);
				}
				Renderer2D::DrawQuad({ s_MapWidth - x - s_MapWidth / 2.0f, s_MapHeight - y - s_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, subTexture);
			}
		}

		Renderer2D::EndScene();
		m_FrameBuffer->Unbind();

		if(!stopGraph)
		{
			if (m_TimeSteps.size() == m_TimeStepsMaxCount)
			{
				m_TimeSteps.erase(m_TimeSteps.begin());
			} else if(m_TimeSteps.size() > m_TimeStepsMaxCount)
			{
				m_TimeSteps.erase(m_TimeSteps.begin());
				m_TimeSteps.erase(m_TimeSteps.begin());
			}
			m_TimeSteps.push_back(timeStep.GetMilliseconds());
		}
	}

}

