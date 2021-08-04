#pragma once
#include <string>

#include <glm/glm.hpp>
#include "FoxEngine/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace FoxEngine
{
	class OpenGLShader : public Shader
	{
	public:
		uint32_t rendererId;
		std::string name;
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader() override;

		void bind() override;
		void unbind() override;
		
		virtual const std::string& getName() const override { return name; }

		void setUniformInt(const std::string& name, int value) override;
		void setUniformIntArray(const std::string& name, int* values, uint32_t count) override;
		
		void setUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		void setUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		
		void setUniformFloat(const std::string& name, float value) override;
		void setUniformFloat2(const std::string& name, const glm::vec2& values) override;
		void setUniformFloat3(const std::string& name, const glm::vec3& values) override;
		void setUniformFloat4(const std::string& name, const glm::vec4& values) override;
	private:
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::string readFile(const std::string& path);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
	};
}
