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
		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);

	};
}
