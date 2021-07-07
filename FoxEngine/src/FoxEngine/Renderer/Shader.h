 #pragma once
#include <string>

#include "glm/glm.hpp"

 namespace FoxEngine
{
	class Shader
	{
	public:
		uint32_t m_RendererId;
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader();

		void Bind();
		void Unbind();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		static std::shared_ptr<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	};
}
