#include "fepch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "FoxEngine/Platform/OpenGL/OpenGLShader.h"
#include "FoxEngine/Renderer/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace FoxEngine
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Storage;
	
	void Renderer2D::Init()
	{
		s_Storage = new Renderer2DStorage();
		s_Storage->QuadVertexArray = VertexArray::Create();
		s_Storage->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
		};

		FoxEngine::BufferLayout layout = {
			{FoxEngine::ShaderDataType::Float3, "a_Position"},
		};

		FoxEngine::Ref<FoxEngine::VertexBuffer> vertexBuffer = FoxEngine::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout(layout);

		s_Storage->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 0, 3, 2 };

		FoxEngine::Ref<FoxEngine::IndexBuffer> indexBuffer = FoxEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		s_Storage->QuadVertexArray->SetIndexBuffer(indexBuffer);
		s_Storage->FlatColorShader = FoxEngine::Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::ShutDown()
	{
		delete s_Storage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Storage->FlatColorShader->Bind();
		s_Storage->FlatColorShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Storage->FlatColorShader->Bind();
		s_Storage->FlatColorShader->SetUniformFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Storage->FlatColorShader->SetUniformMat4("u_Transform", transform);
		
		s_Storage->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage->QuadVertexArray);
	}
}
