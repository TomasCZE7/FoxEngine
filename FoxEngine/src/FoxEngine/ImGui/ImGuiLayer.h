#pragma once
#include "FoxEngine/Core/Layer.h"

namespace FoxEngine {

	class ImGuiLayer : public Layer
	{
	private:
		float m_Time;
		bool m_BlockEvents = true;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void Begin();
		virtual void End();

		void OnEvent(Event& event) override;
		
		void SetBlockEvents(bool block) { m_BlockEvents = block; }
		
	private:
		
	};

}