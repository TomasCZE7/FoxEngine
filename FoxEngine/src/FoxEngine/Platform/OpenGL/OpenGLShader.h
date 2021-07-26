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
		uint32_t m_RendererId;
		std::string m_Name;
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader() override;

		void Bind() override;
		void Unbind() override;
		
		virtual const std::string& GetName() const override { return m_Name; }

		void SetUniformInt(const std::string& name, int value) override;
		void SetUniformIntArray(const std::string& name, int* values, uint32_t count) override;
		
		void SetUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override ;
		
		void SetUniformFloat(const std::string& name, float value) override;
		void SetUniformFloat2(const std::string& name, const glm::vec2& values) override;
		void SetUniformFloat3(const std::string& name, const glm::vec3& values) override;
		void SetUniformFloat4(const std::string& name, const glm::vec4& values) override;
	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	};
}
