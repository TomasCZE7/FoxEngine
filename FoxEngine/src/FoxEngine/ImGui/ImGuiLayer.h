#pragma once
#include "FoxEngine/Core/Layer.h"
#include "FoxEngine/Event/KeyboardEvent.h"
#include "FoxEngine/Event/MouseEvent.h"
#include "FoxEngine/Event/WindowEvent.h"

namespace FoxEngine {

	class FOX_API ImGuiLayer : public Layer
	{
	private:
		float m_Time;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void Begin();
		virtual void End();
		
	private:
		
	};

}