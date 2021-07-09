#include "fepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxEngine
{
	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
