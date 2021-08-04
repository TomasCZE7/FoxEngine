#include "fepch.h"
#include "FrameBuffer.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLFrameBuffer.h"

namespace FoxEngine
{
	Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecification& specification)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::NONE: return nullptr;
			case RendererAPI::API::OPENGL: return std::make_shared<OpenGLFrameBuffer>(specification);
		}
		FOX_CORE_ASSERT(false, "Unknown Rednerer API!");
		return nullptr;
	}
}
