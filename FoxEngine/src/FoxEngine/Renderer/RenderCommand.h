#pragma once
#include "RendererAPI.h"

namespace FoxEngine
{
	class RenderCommand
	{
	private:
		static RendererAPI* rendererApi;
	public:
		inline static void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
            rendererApi->drawIndexed(vertexArray, indexCount);
		}

		inline static void setClearColor(const glm::vec4& color)
		{
            rendererApi->setClearColor(color);
		}

		inline static void clear()
		{
            rendererApi->clear();
		}

		inline static void init()
		{
			rendererApi->init();
		}

		inline static void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
            rendererApi->setViewPort(x, y, width, height);
		}
	};
}
