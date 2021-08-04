#include "fepch.h"
#include "FoxEngine/Scene/Scene.h"

#include "Components.h"
#include "FoxEngine/Renderer/Renderer2D.h"

#include "Entity.h"

namespace FoxEngine
{ 
	Scene::Scene()
	{
		entt::entity entity = registry.create();
	}

	Scene::~Scene()
	{
		
	}
	
	Entity Scene::createEntity(char* name)
	{
		Entity entity = {registry.create(), this };
        entity.addComponent<TransformComponent>();
        entity.addComponent<NameComponent>(name);
		return entity;
	}

	void Scene::onUpdate(TimeStep ts)
	{
		auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for(auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::drawQuad(transform, sprite.color);
		}  
	}
}
