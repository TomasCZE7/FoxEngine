#pragma once
#include "OrthographicCamera.h"
#include "Camera.h"
#include "SubTexture2D.h"

#include "Texture.h"

namespace FoxEngine
{
	class Renderer2D
	{
	public:
		static void init();
		static void shutDown();
		
		static void beginScene(const OrthographicCamera& camera);
		static void beginScene(const Camera& camera, const glm::mat4& transform);
		static void flush();
		static void endScene();

		
		//Primitives
		static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void drawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);
		static void drawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);


		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);

		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);

		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		
		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& textures, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);

		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, const glm::vec4& textureTint = glm::vec4(
                1.0f), float textureTilingFactor = 1.0f);

		struct Statistics {
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;

			uint32_t getTotalVertexCount() { return quadCount * 4; }
			uint32_t getTotalIndexCount() { return quadCount * 6; }
		};
		
		static void resetStats();
		static Statistics getStats();
	private:
		static void startNewBatch();
	};
}
