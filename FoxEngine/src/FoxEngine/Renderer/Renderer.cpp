#include "fepch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "FoxEngine/Renderer/Renderer2D.h"

namespace FoxEngine
{

	Renderer::SceneData* Renderer::sceneData = new SceneData();
	
	void Renderer::beginScene(OrthographicCamera& camera)
	{
        sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene()
	{
	}

	void Renderer::submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform)
	{
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_ViewProjection",
                                                                        sceneData->viewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_Transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
	}

	void Renderer::init()
	{
        RenderCommand::init();
        Renderer2D::init();
	}

	void Renderer::onWindowResized(uint32_t width, uint32_t height)
	{
        RenderCommand::setViewPort(0, 0, width, height);
	}
}
