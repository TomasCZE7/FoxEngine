#include "fepch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace FoxEngine
{

	Renderer::SceneData* Renderer::m_SceneData = new SceneData();
	
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const Object& object)
	{
		Submit(object.GetVertexArray(), object.GetRawShader(), object.GetTransform());
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}
}
