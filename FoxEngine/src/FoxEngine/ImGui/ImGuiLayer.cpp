#include "fepch.h"
#include "ImGuiLayer.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "FoxEngine/Core/Application.h"

#include <glad/glad.h>


namespace FoxEngine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui Layer") {
		
	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::onAttach() {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::getInstance();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);

        ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	

	void ImGuiLayer::end() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getInstance();

		io.DisplaySize = ImVec2((float) app.getWindow().getWidth(), (float) app.getWindow().getHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::onEvent(Event& event)
	{
		if (m_BlockEvents) {
			ImGuiIO& io = ImGui::GetIO();
			event.handled |= event.isInCategory(EVENT_CATEGORY_MOUSE) & io.WantCaptureMouse;
			event.handled |= event.isInCategory(EVENT_CATEGORY_KEYBOARD) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::onImGuiRender() {
		//static bool show = false;
		//ImGui::ShowDemoWindow(&show);
	}

}
