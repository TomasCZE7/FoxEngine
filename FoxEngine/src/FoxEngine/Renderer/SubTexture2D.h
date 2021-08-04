#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace FoxEngine
{
	class SubTexture2D
	{
	private:
		Ref<Texture2D> texture;
		glm::vec2 textureCoords[4];

	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const glm::vec2* getTextureCoords() const { return textureCoords; }
		const Ref<Texture2D> getTexture() const { return texture; }

		static Ref<SubTexture2D> createFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = {1.0f, 1.0f}, const float gap = 0.0f);
	};
}