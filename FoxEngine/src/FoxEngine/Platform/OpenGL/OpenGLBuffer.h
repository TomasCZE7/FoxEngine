#pragma once

#include "FoxEngine/Renderer/Buffer.h"

namespace FoxEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t RendererId;
		BufferLayout m_Layout;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual void SetData(const void* data, uint32_t size) override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t RendererId;
		uint32_t Count;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const { return Count; }
		
		virtual void Bind() const;
		virtual void Unbind() const;

	};
}