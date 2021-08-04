#include "fepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace FoxEngine
{
	Ref<VertexArray> VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::NONE: return nullptr;
			case RendererAPI::API::OPENGL: return std::make_shared<OpenGLVertexArray>();
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
