 #pragma once
#include <string>

#include "VertexArray.h"
#include <glm/glm.hpp>

 namespace FoxEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetUniformInt(const std::string& name, int value) = 0;

		virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void SetUniformFloat(const std::string& name, float value)= 0;
		virtual void SetUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& values) = 0;

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
