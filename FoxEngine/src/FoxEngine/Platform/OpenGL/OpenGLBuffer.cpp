#include "fepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace FoxEngine
{
	
	//VertexBuffer -----------------------------------
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		FOX_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &RendererId);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, RendererId);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, RendererId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	//IndexBuffer -----------------------------------
	
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: Count(count)
	{
		glCreateBuffers(1, &RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &RendererId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererId);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
