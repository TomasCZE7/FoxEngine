#pragma once
#include <string>

namespace FoxEngine
{
	class Shader
	{
	private:
		uint32_t m_RendererId;
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		Shader() {}
		virtual ~Shader();

		void Bind();
		void Unbind();
	};
}