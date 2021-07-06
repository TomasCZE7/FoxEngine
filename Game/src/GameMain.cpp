#include <FoxEngine.h>

#include "imgui/imgui.h"
#include "FoxEngine/Renderer/Buffer.h"
#include "FoxEngine/Renderer/VertexArray.h"
#include "FoxEngine/Renderer/Renderer.h"

class ExampleLayer : public FoxEngine::Layer {
public:

	std::shared_ptr<FoxEngine::VertexArray> m_TriangleVertexArray;
	std::shared_ptr<FoxEngine::VertexBuffer> m_TriangleVertexBuffer;
	std::shared_ptr<FoxEngine::IndexBuffer> m_TriangleIndexBuffer;
	std::shared_ptr<FoxEngine::Shader> m_TriangleShader;
	

	
	ExampleLayer()
		:Layer("Example")
	{
		prepareTriangle();
	}

	void prepareTriangle()
	{
		m_TriangleVertexArray.reset(FoxEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0, 1.0f
		};

		m_TriangleVertexBuffer.reset(FoxEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		FoxEngine::BufferLayout layout = {
			{FoxEngine::ShaderDataType::Float3, "a_Position"},
			{FoxEngine::ShaderDataType::Float4, "a_Color"}
		};
		m_TriangleVertexBuffer->SetLayout(layout);

		m_TriangleVertexArray->AddVertexBuffer(m_TriangleVertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		m_TriangleIndexBuffer.reset(FoxEngine::IndexBuffer::Create(indices, 3));
		m_TriangleVertexArray->SetIndexBuffer(m_TriangleIndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main(){
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;
		
			in vec4 v_Color;
		
			void main(){
				o_Color = v_Color;
			}

		)";

		m_TriangleShader.reset(new FoxEngine::Shader(vertexSource, fragmentSource));
	}
	
	
	void OnUpdate() {
		FoxEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		FoxEngine::RenderCommand::Clear();

		FoxEngine::Renderer::BeginScene();

		m_TriangleShader->Bind();
		FoxEngine::Renderer::Submit(m_TriangleVertexArray);

		FoxEngine::Renderer::EndScene();
		
		
	}

	void OnEvent(FoxEngine::Event& event) {
	}

	virtual void OnImGuiRender() override
	{
	}

};

class GameMain : public FoxEngine::Application
{

public:
	GameMain()
	{
		PushLayer(new ExampleLayer());
	}
	~GameMain()
	{
		
	}
	
};

FoxEngine::Application* FoxEngine::CreateApplication()
{
	return new GameMain();
}