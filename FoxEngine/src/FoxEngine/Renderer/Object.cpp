#include "fepch.h"
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>

namespace FoxEngine
{
	Object::Object(Ref<VertexArray> vertexArray, glm::vec3 position)
		:m_VertexArray(vertexArray), m_Transform(glm::mat4(1.0f)){
		SetPosition(position);
	}

	Ref<VertexBuffer> Object::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, BufferLayout& layout)
	{
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		return vertexBuffer;
	}

	Ref<VertexBuffer> Object::AddVertexBuffer(float* vertices, uint32_t size, BufferLayout& layout)
	{
		Ref<VertexBuffer> vb = VertexBuffer::Create(vertices, size);
		vb->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vb);
		return vb;
		
	}

	Ref<IndexBuffer> Object::SetIndexBuffer(uint32_t* indices, uint32_t size)
	{
		Ref<IndexBuffer> ib = IndexBuffer::Create(indices, size);
		m_VertexArray->SetIndexBuffer(ib);
		return ib;
	}

	void Object::SetPosition(glm::vec3 position)
	{
		m_Position = position;
		m_Transform = glm::translate(glm::mat4(1.0f), m_Position);
	}
}
