#pragma once
#include "FoxEngine/Renderer/VertexArray.h"

namespace FoxEngine
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		Ref<IndexBuffer> m_IndexBuffer;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		uint32_t RendererId;
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	};
}
