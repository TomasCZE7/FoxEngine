#include "fepch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "FoxEngine/Platform/OpenGL/OpenGLShader.h"
#include "FoxEngine/Renderer/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace FoxEngine
{
	
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DStorage
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture> WhiteTexture;
		
		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DStorage s_Storage;
	
	void Renderer2D::Init()
	{
		s_Storage.QuadVertexArray = VertexArray::Create();
		s_Storage.TextureShader = Shader::Create("assets/shaders/FlatColor.glsl");

		BufferLayout layout = {

		};

		s_Storage.QuadVertexBuffer = VertexBuffer::Create(s_Storage.MaxVertices * sizeof(QuadVertex));
		s_Storage.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});

		s_Storage.QuadVertexArray->AddVertexBuffer(s_Storage.QuadVertexBuffer);

		s_Storage.QuadVertexBufferBase = new QuadVertex[s_Storage.MaxVertices];

		uint32_t* indices = new uint32_t[s_Storage.MaxIndices];

		uint32_t offset = 0;
		for(uint32_t i = 0; i < s_Storage.MaxIndices; i+= 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3; 
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, s_Storage.MaxIndices);

		s_Storage.QuadVertexArray->SetIndexBuffer(indexBuffer);

		delete[] indices;
		
		s_Storage.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Storage.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		
		s_Storage.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Storage.TextureShader->Bind();
		s_Storage.TextureShader->SetUniformInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		
		s_Storage.TextureShader->Bind();
		s_Storage.TextureShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;
		s_Storage.QuadIndexCount = 0;
	}

	void Renderer2D::EndScene()
	{
		FOX_PROFILE_FUNCTION();
		uint32_t dataSize = (uint8_t*)s_Storage.QuadVertexBufferPtr - (uint8_t*)s_Storage.QuadVertexBufferBase;
		
		s_Storage.QuadVertexBuffer->SetData(s_Storage.QuadVertexBufferBase, dataSize);
		
		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray, s_Storage.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Storage.QuadVertexBufferPtr->Position = position;
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f, };
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f, };
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f, };
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Storage.QuadVertexBufferPtr->Color = color;
		s_Storage.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f, };
		s_Storage.QuadVertexBufferPtr++;

		s_Storage.QuadIndexCount += 6;
		
/*		s_Storage.TextureShader->SetUniformFloat("u_TextureMultiplier", 1.0f); 
		s_Storage.WhiteTexture->Bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Storage.TextureShader->SetUniformMat4("u_Transform", transform);
		
		s_Storage.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);*/
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture,
		const glm::vec4& textureTint)
	{
		DrawQuad({ position.x, position.y, 0.0f}, size, texture, textureTint);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
	                          const glm::vec4& textureTint)
	{
		s_Storage.TextureShader->SetUniformFloat4("u_Color", textureTint);
		s_Storage.TextureShader->SetUniformFloat("u_TextureMultiplier", 1.0f);
		s_Storage.TextureShader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Storage.TextureShader->SetUniformMat4("u_Transform", transform);

		texture->Bind();

		s_Storage.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
		const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
		const glm::vec4& color)
	{
		s_Storage.TextureShader->SetUniformFloat4("u_Color", color);
		s_Storage.TextureShader->SetUniformFloat("u_TextureMultiplier", 1.0f);
		s_Storage.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Storage.TextureShader->SetUniformMat4("u_Transform", transform);

		s_Storage.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
		const Ref<Texture2D>& texture, const glm::vec4& textureTint)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, textureTint);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
		const Ref<Texture2D>& texture, const glm::vec4& textureTint)
	{
		s_Storage.TextureShader->SetUniformFloat4("u_Color", textureTint);
		s_Storage.TextureShader->SetUniformFloat("u_TextureMultiplier", 1.0f);
		s_Storage.TextureShader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Storage.TextureShader->SetUniformMat4("u_Transform", transform);

		texture->Bind();

		s_Storage.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray);
	}
}
