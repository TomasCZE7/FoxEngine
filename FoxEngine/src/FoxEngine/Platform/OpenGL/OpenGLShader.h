#pragma once
#pragma once
#include <string>

#include <glm/glm.hpp>
#include "FoxEngine/Renderer/Shader.h"

namespace FoxEngine
{
	class OpenGLShader : public Shader
	{
	public:
		uint32_t m_RendererId;
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		void Bind();
		void Unbind();


		void UploadUniformInt(const std::string& name, int value);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
	};
}
