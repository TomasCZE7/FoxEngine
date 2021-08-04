#pragma once

#include "FoxEngine/Renderer/Buffer.h"

namespace FoxEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t rendererId;
		BufferLayout layout;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		
		virtual void setLayout(const BufferLayout& layout) override { this->layout = layout; }
		virtual void setData(const void* data, uint32_t size) override;
		virtual const BufferLayout& getLayout() const override { return layout; }
	
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t rendererId;
		uint32_t count;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t getCount() const { return count; }
		
		virtual void bind() const;
		virtual void unbind() const;

	};
}