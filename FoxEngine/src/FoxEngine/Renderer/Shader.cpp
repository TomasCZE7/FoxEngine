#include "fepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "FoxEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxEngine
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
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

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		FOX_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists with this name.");
		m_Shaders[name] = shader;
	}
	
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		FOX_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found.");
		return m_Shaders[name];
	}
}
