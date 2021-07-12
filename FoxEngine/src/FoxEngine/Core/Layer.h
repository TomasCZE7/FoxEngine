#pragma once

#include "Core.h"
#include "FoxEngine/Core/TimeStep.h"
#include "FoxEngine/Event/Event.h"
#include "FoxEngine/Renderer/Object.h"
#include "FoxEngine/Renderer/OrthographicCamera.h"

namespace FoxEngine {

	class FOX_API Layer {
	protected:
		std::string m_Name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep timeStep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_Name; }
	};

}
