#pragma once

#include "Core.h"
#include "FoxEngine/Core/TimeStep.h"
#include "FoxEngine/Event/Event.h"
#include "FoxEngine/Renderer/OrthographicCamera.h"

namespace FoxEngine {

	class FOX_API Layer {
	protected:
		std::string name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(TimeStep timeStep) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return name; }
		inline const std::string* const getNamePtr() const { return &name; }

    };

}
