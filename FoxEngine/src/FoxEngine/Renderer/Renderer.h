#pragma once
#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "FoxEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxEngine
{

	class Renderer
	{
	public:
		static void beginScene(OrthographicCamera& camera);
		static void endScene();

		static void submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform = glm::mat4(1.0f));
		
		inline static RendererAPI::API getAPI() { return RendererAPI::getApi(); }
		static void init();
		static void onWindowResized(uint32_t width, uint32_t height);
	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};
		static SceneData* sceneData;
		
	};
}
