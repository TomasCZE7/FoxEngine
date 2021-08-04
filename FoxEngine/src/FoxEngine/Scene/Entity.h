#pragma once

#include "Scene.h"
#include <entt.hpp>

namespace FoxEngine
{
	class Entity
	{
	private:
		entt::entity entity{entt::null };
		Scene* scene = nullptr;
	public:
		Entity() = default;
		Entity(entt::entity entity, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T>
		bool hasComponent(){
			return scene->registry.has<T>(entity);
		}

		template<typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			return scene->registry.emplace<T>(entity, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent()
		{
			return scene->registry.has<T>(entity);
		}

		template<typename T>
		void removeComponent()
		{
			scene->registry.remove<T>(entity);
		}

		operator bool() const { return entity != entt::null; }
	};
}