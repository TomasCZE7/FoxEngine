 #pragma once
#include <string>

#include "VertexArray.h"

 namespace FoxEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const std::string& GetName() const = 0;
		
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static Ref<Shader> Create(const std::string& path);

	};

 	class ShaderLibrary
 	{
	private:
 		//<Name, Shader>
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
 	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Load(const std::string& filepath);

		Ref<Shader> Get(const std::string& name);
 	};
}
