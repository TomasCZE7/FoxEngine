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
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform = glm::mat4(1.0f));
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static void Init();
		static void OnWindowResized(uint32_t width, uint32_t height);
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			~SceneData()
			{
				FOX_CORE_DEBUG("SD deleted");
			}
		};
		static SceneData* m_SceneData;
		
	};
}
