#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace FoxEngine
{
	class SubTexture2D
	{
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TextureCoords[4];

	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const glm::vec2* GetTextureCoords() const { return m_TextureCoords; }
		const Ref<Texture2D> GetTexture() const { return m_Texture; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = {1.0f, 1.0f}, const float gap = 0.0f);
	};
}