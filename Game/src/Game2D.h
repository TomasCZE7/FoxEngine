#pragma once
#include <FoxEngine.h>

class EditorLayer : public FoxEngine::Layer
{
private:
public:
	EditorLayer();
	virtual ~EditorLayer() = default;
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onImGuiRender() override;
	virtual void onEvent(FoxEngine::Event& event) override;
	virtual void onUpdate(FoxEngine::TimeStep timeStep) override;
};

