#pragma once
#include "VertexArray.h"
#include "glm/glm.hpp"

namespace FoxEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0, OPENGL = 1
		};

		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		virtual void init() = 0;
		virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		inline static API getApi() { return api; }
	private:
		static API api;
		
	};
}