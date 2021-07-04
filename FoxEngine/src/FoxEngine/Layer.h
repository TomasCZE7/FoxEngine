#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace FoxEngine {

	class FOX_API Layer {
	protected:
		std::string Name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return Name; }
	};

}