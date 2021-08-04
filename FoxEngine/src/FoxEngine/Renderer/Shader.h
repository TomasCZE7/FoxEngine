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

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void setUniformInt(const std::string& name, int value) = 0;
		virtual void setUniformIntArray(const std::string& name, int* values, uint32_t count) = 0;

		virtual void setUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void setUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void setUniformFloat(const std::string& name, float value)= 0;
		virtual void setUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void setUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void setUniformFloat4(const std::string& name, const glm::vec4& values) = 0;

		virtual const std::string& getName() const = 0;
		
		static Ref<Shader> create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static Ref<Shader> create(const std::string& path);

	};

 	class ShaderLibrary
 	{
	private:
 		//<name, Shader>
		std::unordered_map<std::string, Ref<Shader>> shaders;
 	public:
		void add(const Ref<Shader>& shader);
		void add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> load(const std::string& name, const std::string& filepath);
		Ref<Shader> load(const std::string& filepath);

		Ref<Shader> getByName(const std::string& name);
 	};
}
