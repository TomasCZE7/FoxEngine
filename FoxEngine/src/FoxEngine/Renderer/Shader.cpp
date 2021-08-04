#include "fepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxEngine
{
	Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::NONE: return nullptr;
			case RendererAPI::API::OPENGL: return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::NONE: return nullptr;
		case RendererAPI::API::OPENGL: return std::make_shared<OpenGLShader>(path);
		}
		FOX_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
	{
		FOX_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.End(), "Shader already exists with this name.");
		shaders[name] = shader;
	}
	
	void ShaderLibrary::add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->getName();
        add(name, shader);
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
        add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
        add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::getByName(const std::string& name)
	{
		FOX_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.End(), "Shader not found.");
		return shaders[name];
	}
}
