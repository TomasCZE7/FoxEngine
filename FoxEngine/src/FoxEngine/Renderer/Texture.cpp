#include "fepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLTexture.h"

namespace FoxEngine
{

	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::NONE: return nullptr;
			case RendererAPI::API::OPENGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::NONE: return nullptr;
		case RendererAPI::API::OPENGL: return std::make_shared<OpenGLTexture2D>(width, height);
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
