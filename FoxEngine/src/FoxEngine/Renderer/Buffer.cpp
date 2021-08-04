#include "fepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace FoxEngine
{
	Ref<VertexBuffer> VertexBuffer::create(uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::NONE: return nullptr;
		case RendererAPI::API::OPENGL: return std::make_shared<OpenGLVertexBuffer>(size);
		}
		FOX_CORE_ASSERT(false, "Unknown Rednerer API!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch(Renderer::getAPI())
		{
			case RendererAPI::API::NONE: return nullptr;
			case RendererAPI::API::OPENGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		FOX_CORE_ASSERT(false, "Unknown Rednerer API!");
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::NONE: return nullptr;
			case RendererAPI::API::OPENGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}
		FOX_CORE_ASSERT(false, "Unknown Rednerer API!");
		return nullptr;
	}
}