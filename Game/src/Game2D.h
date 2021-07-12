#pragma once
#include <FoxEngine.h>

class Game2D : public FoxEngine::Layer
{
private:
	FoxEngine::OrthographicCameraController m_CameraController;
	FoxEngine::Ref<FoxEngine::Shader> m_Shader;
	FoxEngine::Ref<FoxEngine::Texture> m_Texture;
	FoxEngine::Ref<FoxEngine::VertexArray> m_VertexArray;
	glm::vec4 m_Color = {0.2f, 0.8f, 0.3f, 0.1f};
public:
	Game2D();
	virtual ~Game2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(FoxEngine::Event& event) override;
	virtual void OnUpdate(FoxEngine::TimeStep timeStep) override;
};

