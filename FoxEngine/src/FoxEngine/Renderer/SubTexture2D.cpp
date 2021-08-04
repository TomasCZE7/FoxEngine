#include "fepch.h"
#include "SubTexture2D.h"

namespace FoxEngine
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: texture(texture) {
        textureCoords[0] = {min.x, min.y };
        textureCoords[1] = {max.x, min.y };
        textureCoords[2] = {max.x, max.y };
        textureCoords[3] = {min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::createFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize,
                                                     const glm::vec2& spriteSize, const float gap)
	{
		glm::vec2 min = {((coords.x * cellSize.x + coords.x * gap) / texture->getWidth()), ((coords.y * cellSize.y + coords.y * gap) /
                texture->getHeight()) };
		glm::vec2 max = {(((coords.x + spriteSize.x) * cellSize.x + coords.x * gap) / texture->getWidth()), (((coords.y + spriteSize.y) * cellSize.y + coords.y * gap) /
                texture->getHeight()) };
		Ref<SubTexture2D> result = std::make_shared<SubTexture2D>(texture, min, max);
		return result;
	}
}
