#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Renderer/Object.h"

namespace FoxEngine {

	class FOX_API Layer {
	protected:
		std::string Name;
		std::vector<Object*> Objects;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		void RenderObjects();

		inline const std::string& GetName() const { return Name; }
		inline const std::vector<Object*> GetObjects() const { return Objects; }
		inline void AddObjects(Object* object) { Objects.push_back(object); }
	};

}
