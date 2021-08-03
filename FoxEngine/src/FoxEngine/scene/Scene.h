#pragma once

#include "entt.hpp"
#include "FoxEngine/Core/TimeStep.h"

namespace FoxEngine
{
	class Entity;
	
	class Scene
	{
	private:
		entt::registry m_Registry;
	public:
		Scene();
		~Scene();

		Entity CreateEntity(char* name = "Entity");

		void OnUpdate(TimeStep ts);

		friend class Entity;
	};
}
