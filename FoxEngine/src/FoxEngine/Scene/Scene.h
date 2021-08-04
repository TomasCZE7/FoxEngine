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
	public:
		Scene();
		~Scene();

		Entity createEntity(char* name = "Entity");

		void onUpdate(TimeStep ts);

		friend class Entity;
	};
}
