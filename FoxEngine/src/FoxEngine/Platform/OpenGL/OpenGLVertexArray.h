#pragma once
#include "FoxEngine/Renderer/VertexArray.h"

namespace FoxEngine
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		Ref<IndexBuffer> indexBuffer;
		std::vector<Ref<VertexBuffer>> vertexBuffers;
		uint32_t rendererId;
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return vertexBuffers; };
		virtual const Ref<IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }
	};
}
