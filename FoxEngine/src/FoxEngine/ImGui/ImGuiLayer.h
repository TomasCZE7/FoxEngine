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

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;
		virtual void begin();
		virtual void end();

		void onEvent(Event& event) override;
		
		void SetBlockEvents(bool block) { m_BlockEvents = block; }
		
	private:
		
	};

}