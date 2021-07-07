#pragma once
#include "VertexArray.h"
#include "Shader.h"


namespace FoxEngine {
	
	class Object
	{
	private:
		std::shared_ptr<VertexArray> m_VertexArray;
		//std::shared_ptr<VertexBuffer> m_VertexBuffer;
		//std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;
	public:
		Object(VertexArray vertexArray);
		inline const std::shared_ptr<VertexArray> GetVertexArray() const { return m_VertexArray; }
		//inline const std::shared_ptr<VertexBuffer> GetVertexBuffers() const { return m_VertexBuffer; }
		//inline const std::shared_ptr<VertexArray> getIndexBuffer() const { return m_IndexBuffer; }
		inline const std::shared_ptr<Shader> GetShader() const { return m_Shader; }
	};

}