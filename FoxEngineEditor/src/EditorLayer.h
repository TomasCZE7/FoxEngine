#pragma once
#include <FoxEngine.h>

namespace FoxEngine
{
	class EditorLayer : public Layer
	{
	private:
		OrthographicCameraController cameraController;
		Ref<Shader> shader;
		Ref<Texture> texture;
		Ref<FrameBuffer> frameBuffer;

		Ref<Texture2D> minecraftGrassTexture;
		Ref<Texture2D> spriteSheet;
		Ref<Texture2D> backgroundSpriteSheet;
		Ref<SubTexture2D> waterTexture, grassTexture, dirtTexture, airTexture, coinTexture, coinFlippedTexture;

		Ref<Scene> activeScene;
		
		std::unordered_map<char, Ref<SubTexture2D>> textureMap;

		glm::vec4 color = {0.2f, 0.8f, 0.3f, 0.1f };

		glm::vec2 viewPortSize;
		bool viewPortFocused = false;
		bool viewPortHovered = false;
		
		std::vector<float> timeSteps;
		int32_t timeStepMaxCount = 120;
		float longestTimeStep = -1.0f;
		float timeStepAverage = -1.0f;
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;
		virtual void onEvent(Event& event) override;
		virtual void onUpdate(TimeStep timeStep) override;
	};
}


