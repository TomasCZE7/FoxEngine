#pragma once

#include "entt.hpp"
#include "FoxEngine/Core/TimeStep.h"

namespace FoxEngine
{
	class Entity;
	
	class Scene
	{
	private:
		entt::registry registry;

		uint32_t viewportWidth = 0, viewportHeight = 0;
	public:
		Scene();
		~Scene();

		Entity createEntity(char* name = "Entity");

		void onUpdate(TimeStep ts);
		void onViewportResize(uint32_t width, uint32_t height);

		friend class Entity;
	};
}
