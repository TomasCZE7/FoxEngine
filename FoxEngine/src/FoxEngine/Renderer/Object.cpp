#include "fepch.h"
#include "Object.h"

namespace FoxEngine
{
	Object::Object(std::shared_ptr<VertexArray> vertexArray)
		:m_VertexArray(vertexArray){
	}

	std::shared_ptr<VertexBuffer> Object::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, BufferLayout& layout)
	{
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		return vertexBuffer;
	}

	std::shared_ptr<VertexBuffer> Object::AddVertexBuffer(float* vertices, uint32_t size, BufferLayout& layout)
	{
		std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(vertices, size);
		vb->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vb);
		return vb;
		
	}

	std::shared_ptr<IndexBuffer> Object::SetIndexBuffer(uint32_t* indices, uint32_t size)
	{
		std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(indices, size);
		m_VertexArray->SetIndexBuffer(ib);
		return ib;
	}
}
