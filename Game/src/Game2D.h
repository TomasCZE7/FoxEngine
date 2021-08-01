#pragma once
#include <FoxEngine.h>

class EditorLayer : public FoxEngine::Layer
{
private:
public:
	EditorLayer();
	virtual ~EditorLayer() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(FoxEngine::Event& event) override;
	virtual void OnUpdate(FoxEngine::TimeStep timeStep) override;
};

