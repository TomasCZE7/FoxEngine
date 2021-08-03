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
		glm::vec2 TextureCoord;
		float TextureIndex;
		float TextureTilingFactor = 1.0f;
	};

	struct Renderer2DStorage
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;
		
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		
		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; //index 0 is White textures

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Statistics;
	};

	static Renderer2DStorage s_Storage;
	
	void Renderer2D::Init()
	{
		s_Storage.QuadVertexArray = VertexArray::Create();
		s_Storage.TextureShader = Shader::Create("assets/shaders/FlatColor.glsl");

		s_Storage.QuadVertexBuffer = VertexBuffer::Create(s_Storage.MaxVertices * sizeof(QuadVertex));
		s_Storage.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TextureIndex" },
			{ ShaderDataType::Float, "a_TextureTilingFactor" }
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

		int32_t samplers[s_Storage.MaxTextureSlots];
		for(uint32_t i = 0; i < s_Storage.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		
		s_Storage.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Storage.TextureShader->Bind();
		s_Storage.TextureShader->SetUniformIntArray("u_Textures", samplers, s_Storage.MaxTextureSlots);

		s_Storage.TextureSlots[0] = s_Storage.WhiteTexture;

		s_Storage.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Storage.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Storage.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_Storage.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::ShutDown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		
		s_Storage.TextureShader->Bind();
		s_Storage.TextureShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Storage.QuadIndexCount = 0;
		s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;

		s_Storage.TextureSlotIndex = 1;
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
		for (uint32_t i = 0; i < s_Storage.TextureSlotIndex; i++)
		{
			auto texture = s_Storage.TextureSlots[i];
			s_Storage.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Storage.QuadVertexArray, s_Storage.QuadIndexCount);
		s_Storage.Statistics.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		const float textureIndex = 0.0f; //White texture
		const size_t quadVertexCount = 4;
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};

		if (s_Storage.QuadIndexCount > s_Storage.MaxIndices)
		{
			StartNewBatch();
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Storage.QuadVertexBufferPtr->Position = transform * s_Storage.QuadVertexPositions[i];
			s_Storage.QuadVertexBufferPtr->Color = color;
			s_Storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
			s_Storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			s_Storage.QuadVertexBufferPtr++;
		}

		s_Storage.QuadIndexCount += 6;
		s_Storage.Statistics.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& textureTint,
		float textureTilingFactor)
	{
		if (s_Storage.QuadIndexCount >= s_Storage.MaxIndices)
		{
			StartNewBatch();
		}

		const size_t quadVertexCount = 4;

		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Storage.TextureSlotIndex; i++) {
			if (*s_Storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Storage.TextureSlotIndex;
			s_Storage.TextureSlots[s_Storage.TextureSlotIndex] = texture;
			s_Storage.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Storage.QuadVertexBufferPtr->Position = transform * s_Storage.QuadVertexPositions[i];
			s_Storage.QuadVertexBufferPtr->Color = textureTint;
			s_Storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
			s_Storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			s_Storage.QuadVertexBufferPtr->TextureTilingFactor = textureTilingFactor;
			s_Storage.QuadVertexBufferPtr++;
		}

		s_Storage.QuadIndexCount += 6;
		s_Storage.Statistics.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture,
		const glm::vec4& textureTint, float textureTilingFactor)
	{
		if (s_Storage.QuadIndexCount >= s_Storage.MaxIndices)
		{
			StartNewBatch();
		}

		const size_t quadVertexCount = 4;

		const glm::vec2* textureCoords = subTexture->GetTextureCoords();
		const Ref<Texture2D> texture = subTexture->GetTexture();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Storage.TextureSlotIndex; i++) {
			if (*s_Storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Storage.TextureSlotIndex;
			s_Storage.TextureSlots[s_Storage.TextureSlotIndex] = texture;
			s_Storage.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Storage.QuadVertexBufferPtr->Position = transform * s_Storage.QuadVertexPositions[i];
			s_Storage.QuadVertexBufferPtr->Color = textureTint;
			s_Storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
			s_Storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			s_Storage.QuadVertexBufferPtr->TextureTilingFactor = textureTilingFactor;
			s_Storage.QuadVertexBufferPtr++;
		}

		s_Storage.QuadIndexCount += 6;
		s_Storage.Statistics.QuadCount++;
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{	
		if(s_Storage.QuadIndexCount > s_Storage.MaxIndices)
		{
			StartNewBatch();
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
		
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture,
		const glm::vec4& textureTint, float textureTilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f}, size, texture, textureTint, textureTilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
	                          const glm::vec4& textureTint, float textureTilingFactor)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, textureTint, textureTilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture,
		const glm::vec4& textureTint, float textureTilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, subTexture, textureTint, textureTilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture,
		const glm::vec4& textureTint, float textureTilingFactor)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, subTexture, textureTint, textureTilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
	                                 const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
		const glm::vec4& color)
	{
		if (s_Storage.QuadIndexCount >= s_Storage.MaxIndices)
		{
			StartNewBatch();
		}
		const float textureIndex = 0.0f;
		const size_t quadVertexCount = 4;
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Storage.QuadVertexBufferPtr->Position = transform * s_Storage.QuadVertexPositions[i];
			s_Storage.QuadVertexBufferPtr->Color = color;
			s_Storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
			s_Storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			s_Storage.QuadVertexBufferPtr++;
		}

		s_Storage.QuadIndexCount += 6;
		s_Storage.Statistics.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
		const Ref<Texture2D>& texture, const glm::vec4& textureTint, float textureTilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, textureTint, textureTilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
		const Ref<Texture2D>& texture, const glm::vec4& textureTint, float textureTilingFactor)
	{
		if (s_Storage.QuadIndexCount >= s_Storage.MaxIndices)
		{
			StartNewBatch();
		}
		float textureIndex = 0.0f;
		const size_t quadVertexCount = 4;
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		for (uint32_t i = 1; i < s_Storage.TextureSlotIndex; i++) {
			if (*s_Storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Storage.TextureSlotIndex;
			s_Storage.TextureSlots[s_Storage.TextureSlotIndex] = texture;
			s_Storage.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Storage.QuadVertexBufferPtr->Position = transform * s_Storage.QuadVertexPositions[i];
			s_Storage.QuadVertexBufferPtr->Color = textureTint;
			s_Storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
			s_Storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			s_Storage.QuadVertexBufferPtr++;
		}

		s_Storage.QuadIndexCount += 6;
		s_Storage.Statistics.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
		const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint, float textureTilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, subTexture, textureTint, textureTilingFactor);

	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
		const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint, float textureTilingFactor)
	{
		if (s_Storage.QuadIndexCount >= s_Storage.MaxIndices)
		{
			StartNewBatch();
		}

		const size_t quadVertexCount = 4;

		const glm::vec2* textureCoords = subTexture->GetTextureCoords();
		const Ref<Texture2D> texture = subTexture->GetTexture();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Storage.TextureSlotIndex; i++) {
			if (*s_Storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Storage.TextureSlotIndex;
			s_Storage.TextureSlots[s_Storage.TextureSlotIndex] = texture;
			s_Storage.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Storage.QuadVertexBufferPtr->Position = transform * s_Storage.QuadVertexPositions[i];
			s_Storage.QuadVertexBufferPtr->Color = textureTint;
			s_Storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
			s_Storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			s_Storage.QuadVertexBufferPtr->TextureTilingFactor = textureTilingFactor;
			s_Storage.QuadVertexBufferPtr++;
		}

		s_Storage.QuadIndexCount += 6;
		s_Storage.Statistics.QuadCount++;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Storage.Statistics, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Storage.Statistics;
	}

	void Renderer2D::StartNewBatch()
	{
		EndScene();
		
		s_Storage.QuadVertexBufferPtr = s_Storage.QuadVertexBufferBase;
		s_Storage.QuadIndexCount = 0;

		s_Storage.TextureSlotIndex = 1;
	}

}
