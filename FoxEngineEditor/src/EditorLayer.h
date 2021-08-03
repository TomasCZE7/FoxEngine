#pragma once
#include <FoxEngine.h>

namespace FoxEngine
{
	class EditorLayer : public Layer
	{
	private:
		OrthographicCameraController m_CameraController;
		Ref<Shader> m_Shader;
		Ref<Texture> m_Texture;
		Ref<VertexArray> m_VertexArray;
		Ref<FrameBuffer> m_FrameBuffer;

		Ref<Texture2D> m_MinecraftGrassTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<Texture2D> m_BackgroundSpriteSheet;
		Ref<SubTexture2D> m_WaterTexture, m_GrassTexture, m_DirtTexture, m_AirTexture, m_CoinTexture, m_CoinFlippedTexture;

		Ref<Scene> m_ActiveScene;
		
		std::unordered_map<char, Ref<SubTexture2D>> s_TextureMap;

		glm::vec4 m_Color = { 0.2f, 0.8f, 0.3f, 0.1f };

		glm::vec2 m_ViewPortSize;
		bool m_ViewPortFocused = false;
		bool m_ViewPortHovered = false;
		
		std::vector<float> m_TimeSteps;
		int32_t m_TimeStepsMaxCount = 120;
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
		virtual void OnUpdate(TimeStep timeStep) override;
	};
}


