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

		void UploadUniformInt(const std::string& name, int value);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	};
}
