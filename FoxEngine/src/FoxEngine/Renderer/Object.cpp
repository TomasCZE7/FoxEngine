#include "fepch.h"
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>

namespace FoxEngine
{
	Object::Object(std::shared_ptr<VertexArray> vertexArray, glm::vec3 position)
		:m_VertexArray(vertexArray), m_Transform(glm::mat4(1.0f)){
		SetPosition(position);
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

	void Object::SetPosition(glm::vec3 position)
	{
		m_Position = position;
		m_Transform = glm::translate(glm::mat4(1.0f), m_Position);
	}
}
