#pragma once
#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Object.h"
#include "Shader.h"

namespace FoxEngine
{

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform = glm::mat4(1.0f));
		static void Submit(const Object& object);
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static void Init();
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
