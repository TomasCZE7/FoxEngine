#include "fepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLTexture.h"

namespace FoxEngine
{

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
