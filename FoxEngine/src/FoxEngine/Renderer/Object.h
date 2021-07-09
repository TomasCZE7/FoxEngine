#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "FoxEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxEngine {
	
	class Object
	{
	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
		glm::mat4 m_Transform;
		glm::vec3 m_Position;
	public:
		Object(Ref<VertexArray> vertexArray, glm::vec3 position);
		Object(){}
		inline const Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }
		inline const Ref<OpenGLShader> GetShader() const { return std::dynamic_pointer_cast<OpenGLShader>(m_Shader); }
		inline const Ref<Shader> GetRawShader() const { return m_Shader; }
		~Object()
		{
		}

		inline Ref<VertexBuffer> AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) { m_VertexArray->AddVertexBuffer(vertexBuffer); return vertexBuffer; };
		Ref<VertexBuffer> AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, BufferLayout& layout);
		Ref<VertexBuffer> AddVertexBuffer(float* vertices, uint32_t size, BufferLayout& layout);
		inline Ref<IndexBuffer> SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) { m_VertexArray->SetIndexBuffer(indexBuffer); return indexBuffer; };
		Ref<IndexBuffer> SetIndexBuffer(uint32_t* indices, uint32_t size);
		inline Ref<Shader> SetShader(const Ref<Shader>& shader) { m_Shader = shader; return shader;  }
		inline Ref<Shader> SetShader(const std::string& vertexSource, const std::string& fragmentSource ) { return SetShader(FoxEngine::Shader::Create(vertexSource, fragmentSource)); }
		inline Ref<Shader> SetShader(const std::string& path) { return SetShader(FoxEngine::Shader::Create(path)); }

		inline void SetTransform(glm::mat4 transform) { m_Transform = transform; }
		inline const glm::mat4&  GetTransform() const { return m_Transform; }
		inline void SetPosition(glm::vec3 position);
		inline const glm::vec3& GetPosition() const { return m_Position; }
	};

}
