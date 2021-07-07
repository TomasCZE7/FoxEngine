#include "fepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace FoxEngine
{

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch(Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		FOX_CORE_ASSERT(false, "Unknown Rednerer API!");
		return nullptr;
	}


	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}
		FOX_CORE_ASSERT(false, "Unknown Rednerer API!");
		return nullptr;
	}
}