#include "fepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace FoxEngine
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
