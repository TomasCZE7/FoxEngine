#pragma once
#include "FoxEngine/Renderer/RendererAPI.h"

namespace FoxEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void Init() override;
	};

}
