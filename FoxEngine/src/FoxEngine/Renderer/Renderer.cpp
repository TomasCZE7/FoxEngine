#include "fepch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "FoxEngine/Renderer/Renderer2D.h"

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
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}
}
