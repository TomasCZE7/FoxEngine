#include "fepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace FoxEngine
{

	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}
		FOX_ASSERT(false, "Unknown ShaderDataType ({0})", type);
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererId);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(rendererId);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		FOX_ASSERT(vertexBuffer->getLayout().getElements().size, "Vertex buffer has no elements in the layout!");

		glBindVertexArray(rendererId);
        vertexBuffer->bind();
		
		uint32_t index = 0;
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
                                      element.getComponentCount(),
				ShaderDataTypeToOpenGLType(element.Type),
                                      element.normalized ? GL_TRUE : GL_FALSE,
                                      layout.getStride(),
				(const void*)element.offset);
			
			index++;
		}

        vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererId);
        indexBuffer->bind();

        this->indexBuffer = indexBuffer;
	}
}
