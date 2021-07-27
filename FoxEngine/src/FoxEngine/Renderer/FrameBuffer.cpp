#include "fepch.h"
#include "FrameBuffer.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLFrameBuffer.h"

namespace FoxEngine
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(specification);
		}
		FOX_CORE_ASSERT(false, "Unknown Rednerer API!");
		return nullptr;
	}
}
