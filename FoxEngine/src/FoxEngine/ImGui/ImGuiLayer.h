#pragma once
#include "FoxEngine/Layer.h"
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

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyboardKeyPressedEvent(KeyboardKeyPressedEvent& event);
		bool OnKeyboardKeyReleasedEvent(KeyboardKeyReleasedEvent& event);
		bool OnKeyboardTypedEvent(KeyboardTypedEvent& event);
		bool OnWindowResizedEvent(WindowResizedEvent& event);
	};

}