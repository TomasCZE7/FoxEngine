#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

namespace FoxEngine
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), cameraController(1280.0f / 720.0f, true) {
	}

	void EditorLayer::onAttach()
	{
        minecraftGrassTexture = Texture2D::create("assets/textures/minecraft_texture.png");
        spriteSheet = Texture2D::create("assets/textures/platformer_tilemap.png");

        dirtTexture = SubTexture2D::createFromCoords(spriteSheet, {2, 2}, {18, 18});
        waterTexture = SubTexture2D::createFromCoords(spriteSheet, {13, 5}, {18, 18});

		FrameBufferSpecification specification;
		specification.width = 1280;
		specification.height = 720;

        frameBuffer = FrameBuffer::create(specification);

        cameraController.setZoomLevel(5.0f);

        activeScene = createRef<Scene>();
		
		Entity square = activeScene->createEntity();
        square.addComponent<SpriteRendererComponent>(glm::vec4{0.2f, 0.8f, 0.3f, 1.0f});

        cameraEntity = activeScene->createEntity("Camera");
        square.addComponent<CameraComponent>();
	}

	void EditorLayer::onDetach()
	{

	}


	bool stopGraph = false;
	void EditorLayer::onImGuiRender()
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
		// and handle the pass-thru hole, so we ask begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if begin() returns false (aka window is collapsed).
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
				if (ImGui::MenuItem("Exit")) { Application::getInstance().shutdown(); }

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Renderer2D Statistics");

		auto stats = Renderer2D::getStats();
		ImGui::Text("Draw Calls: %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());
		ImGui::End();

		ImGui::Begin("Renderer performance");
		float* p = &timeSteps[0];
		ImVec2 performanceSize = ImGui::GetContentRegionAvail();
		if(cameraController.getMouseState() == MouseState::MOVING_CAMERA)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
		}
		//ImGui::GetForegroundDrawList()->AddImage((void*)minecraftGrassTexture->getRendererId(), { io.MousePos.x - 25 , io.MousePos.y - 25 }, { io.MousePos.x + 25 , io.MousePos.y + 25 }, {0,1}, {1, 0});
		ImGui::PlotLines("Framerate (ms)", p, timeSteps.size(), 0, "Framerate (ms)", 0, 100, ImVec2{performanceSize.x, 128 });
		if(ImGui::Button("Toggle pause"))
		{
			stopGraph = !stopGraph;
		}

		ImGui::SliderInt("TimeStep count", &timeStepMaxCount, 2, 1000);

        if (timeSteps.size() != 0) {
            timeStepAverage = std::accumulate( timeSteps.begin(), timeSteps.end(), 0.0) / timeSteps.size();
        }

		ImGui::Text("Framerate: %f ms", timeSteps[timeSteps.size() - 1]);
		ImGui::Text("Longest frame: %f ms", longestTimeStep);
		if(timeStepAverage < 17.5f){
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(50, 200, 50, 255));
		} else{
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(225, 50, 50, 255));
        }
		ImGui::Text("Last %d average: %f ms", timeStepMaxCount, timeStepAverage);
        ImGui::PopStyleColor();
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Scene");
        viewPortFocused = ImGui::IsWindowFocused();
        viewPortHovered = ImGui::IsWindowHovered();
        Application::getInstance().getImGuiLayer()->SetBlockEvents(!viewPortFocused || !viewPortHovered);

		ImVec2 imViewPortSize = ImGui::GetContentRegionAvail();
		if(this->viewPortSize != *((glm::vec2*)&imViewPortSize))
		{
            this->viewPortSize = {imViewPortSize.x, imViewPortSize.y };
            frameBuffer->resize((uint32_t) this->viewPortSize.x, (uint32_t) imViewPortSize.y);
            cameraController.onResize(this->viewPortSize.x, this->viewPortSize.y);
            activeScene->onViewportResize((uint32_t) this->viewPortSize.x, (uint32_t) imViewPortSize.y);
		}
		uint32_t textureId = frameBuffer->getColorAttachmentRendererId();
		ImGui::Image((void*)textureId, {this->viewPortSize.x, this->viewPortSize.y }, ImVec2{0, 1 }, ImVec2{1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();
		
		ImGui::End();
	}

	void EditorLayer::onEvent(Event& event)
	{
        cameraController.onEvent(event);
	}

	int32_t animation = 0; //todo
	void EditorLayer::onUpdate(TimeStep timeStep)
	{
		if (animation > 0 && animation % 30 == 0)
		{
			animation = -30;
		}
		
		animation++;

		if(timeStep > longestTimeStep)
            longestTimeStep = timeStep;
		FOX_PROFILE_FUNCTION();
		if(viewPortFocused && viewPortHovered)
            cameraController.onUpdate(timeStep);
		{
			FOX_PROFILE_SCOPE("Render preparation");
            frameBuffer->bind();
            RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::clear();
		}
        Renderer2D::resetStats();

        activeScene->onUpdate(timeStep);

        Renderer2D::endScene();
        frameBuffer->unbind();

		if(!stopGraph)
		{
			if (timeSteps.size() == timeStepMaxCount)
			{
				timeSteps.erase(timeSteps.begin());
			} else if(timeSteps.size() > timeStepMaxCount)
			{
				timeSteps.erase(timeSteps.begin());
				timeSteps.erase(timeSteps.begin());
			}
			timeSteps.push_back(timeStep);
		}
	}

}

