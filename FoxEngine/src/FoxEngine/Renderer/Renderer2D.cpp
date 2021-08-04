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

	static Renderer2DStorage storage;
	
	void Renderer2D::init()
	{
        storage.QuadVertexArray = VertexArray::create();
        storage.TextureShader = Shader::create("assets/shaders/FlatColor.glsl");

        storage.QuadVertexBuffer = VertexBuffer::create(storage.MaxVertices * sizeof(QuadVertex));
        storage.QuadVertexBuffer->setLayout({
                                                      {ShaderDataType::Float3, "a_Position"},
                                                      {ShaderDataType::Float4, "a_Color"},
                                                      {ShaderDataType::Float2, "a_TexCoord"},
                                                      {ShaderDataType::Float,  "a_TextureIndex"},
                                                      {ShaderDataType::Float,  "a_TextureTilingFactor"}
                                              });

        storage.QuadVertexArray->addVertexBuffer(storage.QuadVertexBuffer);

        storage.QuadVertexBufferBase = new QuadVertex[storage.MaxVertices];

		uint32_t* indices = new uint32_t[storage.MaxIndices];

		uint32_t offset = 0;
		for(uint32_t i = 0; i < storage.MaxIndices; i+= 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3; 
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices, storage.MaxIndices);

        storage.QuadVertexArray->setIndexBuffer(indexBuffer);

		delete[] indices;

        storage.WhiteTexture = Texture2D::create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
        storage.WhiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[storage.MaxTextureSlots];
		for(uint32_t i = 0; i < storage.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

        storage.TextureShader = Shader::create("assets/shaders/Texture.glsl");
        storage.TextureShader->bind();
        storage.TextureShader->setUniformIntArray("u_Textures", samplers, storage.MaxTextureSlots);

        storage.TextureSlots[0] = storage.WhiteTexture;

        storage.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f };
        storage.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f };
        storage.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f };
        storage.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::shutDown()
	{
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{

        storage.TextureShader->bind();
        storage.TextureShader->setUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());

        storage.QuadIndexCount = 0;
        storage.QuadVertexBufferPtr = storage.QuadVertexBufferBase;

        storage.TextureSlotIndex = 1;
	}

	void Renderer2D::endScene()
	{
		FOX_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)storage.QuadVertexBufferPtr - (uint8_t*)storage.QuadVertexBufferBase;

        storage.QuadVertexBuffer->setData(storage.QuadVertexBufferBase, dataSize);

        flush();
	}

	void Renderer2D::flush()
	{
		for (uint32_t i = 0; i < storage.TextureSlotIndex; i++)
		{
			auto texture = storage.TextureSlots[i];
            storage.TextureSlots[i]->bind(i);
		}

        RenderCommand::drawIndexed(storage.QuadVertexArray, storage.QuadIndexCount);
		storage.Statistics.drawCalls++;
	}

	void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		const float textureIndex = 0.0f; //White texture
		const size_t quadVertexCount = 4;
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};

		if (storage.QuadIndexCount > storage.MaxIndices)
		{
            startNewBatch();
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
            storage.QuadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[i];
            storage.QuadVertexBufferPtr->Color = color;
            storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
            storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			storage.QuadVertexBufferPtr++;
		}

        storage.QuadIndexCount += 6;
		storage.Statistics.quadCount++;
	}

	void Renderer2D::drawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& textureTint,
                              float textureTilingFactor)
	{
		if (storage.QuadIndexCount >= storage.MaxIndices)
		{
            startNewBatch();
		}

		const size_t quadVertexCount = 4;

		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < storage.TextureSlotIndex; i++) {
			if (*storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)storage.TextureSlotIndex;
            storage.TextureSlots[storage.TextureSlotIndex] = texture;
			storage.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
            storage.QuadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[i];
            storage.QuadVertexBufferPtr->Color = textureTint;
            storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
            storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
            storage.QuadVertexBufferPtr->TextureTilingFactor = textureTilingFactor;
			storage.QuadVertexBufferPtr++;
		}

        storage.QuadIndexCount += 6;
		storage.Statistics.quadCount++;
	}

	void Renderer2D::drawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture,
                              const glm::vec4& textureTint, float textureTilingFactor)
	{
		if (storage.QuadIndexCount >= storage.MaxIndices)
		{
            startNewBatch();
		}

		const size_t quadVertexCount = 4;

		const glm::vec2* textureCoords = subTexture->getTextureCoords();
		const Ref<Texture2D> texture = subTexture->getTexture();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < storage.TextureSlotIndex; i++) {
			if (*storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)storage.TextureSlotIndex;
            storage.TextureSlots[storage.TextureSlotIndex] = texture;
			storage.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
            storage.QuadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[i];
            storage.QuadVertexBufferPtr->Color = textureTint;
            storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
            storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
            storage.QuadVertexBufferPtr->TextureTilingFactor = textureTilingFactor;
			storage.QuadVertexBufferPtr++;
		}

        storage.QuadIndexCount += 6;
		storage.Statistics.quadCount++;
	}


	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
        drawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{	
		if(storage.QuadIndexCount > storage.MaxIndices)
		{
            startNewBatch();
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        drawQuad(transform, color);
		
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                              const glm::vec4& textureTint, float textureTilingFactor)
	{
        drawQuad({position.x, position.y, 0.0f}, size, texture, textureTint, textureTilingFactor);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                              const glm::vec4& textureTint, float textureTilingFactor)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        drawQuad(transform, texture, textureTint, textureTilingFactor);
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture,
                              const glm::vec4& textureTint, float textureTilingFactor)
	{
        drawQuad({position.x, position.y, 0.0f}, size, subTexture, textureTint, textureTilingFactor);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture,
                              const glm::vec4& textureTint, float textureTilingFactor)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        drawQuad(transform, subTexture, textureTint, textureTilingFactor);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
	{
        drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
	{
		if (storage.QuadIndexCount >= storage.MaxIndices)
		{
            startNewBatch();
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
            storage.QuadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[i];
            storage.QuadVertexBufferPtr->Color = color;
            storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
            storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			storage.QuadVertexBufferPtr++;
		}

        storage.QuadIndexCount += 6;
		storage.Statistics.quadCount++;
	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                     const Ref<Texture2D>& textures, const glm::vec4& textureTint, float textureTilingFactor)
	{
        drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, textures, textureTint, textureTilingFactor);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                     const Ref<Texture2D>& texture, const glm::vec4& textureTint, float textureTilingFactor)
	{
		if (storage.QuadIndexCount >= storage.MaxIndices)
		{
            startNewBatch();
		}
		float textureIndex = 0.0f;
		const size_t quadVertexCount = 4;
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		for (uint32_t i = 1; i < storage.TextureSlotIndex; i++) {
			if (*storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)storage.TextureSlotIndex;
            storage.TextureSlots[storage.TextureSlotIndex] = texture;
			storage.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		for (size_t i = 0; i < quadVertexCount; i++)
		{
            storage.QuadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[i];
            storage.QuadVertexBufferPtr->Color = textureTint;
            storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
            storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
			storage.QuadVertexBufferPtr++;
		}

        storage.QuadIndexCount += 6;
		storage.Statistics.quadCount++;
	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                     const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint, float textureTilingFactor)
	{
        drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, subTexture, textureTint, textureTilingFactor);

	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                     const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint, float textureTilingFactor)
	{
		if (storage.QuadIndexCount >= storage.MaxIndices)
		{
            startNewBatch();
		}

		const size_t quadVertexCount = 4;

		const glm::vec2* textureCoords = subTexture->getTextureCoords();
		const Ref<Texture2D> texture = subTexture->getTexture();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < storage.TextureSlotIndex; i++) {
			if (*storage.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)storage.TextureSlotIndex;
            storage.TextureSlots[storage.TextureSlotIndex] = texture;
			storage.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
            storage.QuadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[i];
            storage.QuadVertexBufferPtr->Color = textureTint;
            storage.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
            storage.QuadVertexBufferPtr->TextureIndex = textureIndex;
            storage.QuadVertexBufferPtr->TextureTilingFactor = textureTilingFactor;
			storage.QuadVertexBufferPtr++;
		}

        storage.QuadIndexCount += 6;
		storage.Statistics.quadCount++;
	}

	void Renderer2D::resetStats()
	{
		memset(&storage.Statistics, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::getStats()
	{
		return storage.Statistics;
	}

	void Renderer2D::startNewBatch()
	{
        endScene();

        storage.QuadVertexBufferPtr = storage.QuadVertexBufferBase;
        storage.QuadIndexCount = 0;

        storage.TextureSlotIndex = 1;
	}

}
