#include "fepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace FoxEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
