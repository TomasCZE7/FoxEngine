#pragma once
#include "VertexArray.h"
#include "Shader.h"

namespace FoxEngine {
	
	class Object
	{
	private:
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;
		glm::mat4 m_Transform;
		glm::vec3 m_Position;
	public:
		Object(std::shared_ptr<VertexArray> vertexArray, glm::vec3 position);
		Object(){}
		inline const std::shared_ptr<VertexArray> GetVertexArray() const { return m_VertexArray; }
		inline const std::shared_ptr<Shader> GetShader() const { return m_Shader; }
		~Object()
		{
			FOX_CORE_ERROR("OBJECT deleted");
		}

		inline std::shared_ptr<VertexBuffer> AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) { m_VertexArray->AddVertexBuffer(vertexBuffer); return vertexBuffer; };
		std::shared_ptr<VertexBuffer> AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, BufferLayout& layout);
		std::shared_ptr<VertexBuffer> AddVertexBuffer(float* vertices, uint32_t size, BufferLayout& layout);
		inline std::shared_ptr<IndexBuffer> SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) { m_VertexArray->SetIndexBuffer(indexBuffer); return indexBuffer; };
		std::shared_ptr<IndexBuffer> SetIndexBuffer(uint32_t* indices, uint32_t size);
		inline std::shared_ptr<Shader> SetShader(const std::shared_ptr<Shader>& shader) { m_Shader = shader; return shader;  }
		inline std::shared_ptr<Shader> SetShader(const std::string& vertexSource, const std::string& fragmentSource ) { return SetShader(std::make_shared<FoxEngine::Shader>(vertexSource, fragmentSource)); }

		inline void SetTransform(glm::mat4 transform) { m_Transform = transform; }
		inline const glm::mat4&  GetTransform() const { return m_Transform; }
		inline void SetPosition(glm::vec3 position);
		inline const glm::vec3& GetPosition() const { return m_Position; }
	};

}