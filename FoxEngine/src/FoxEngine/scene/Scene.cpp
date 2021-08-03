#include "fepch.h"
#include "Scene.h"

#include "Components.h"
#include "FoxEngine/Renderer/Renderer2D.h"

#include "Entity.h"

namespace FoxEngine
{ 
	Scene::Scene()
	{
		entt::entity entity = m_Registry.create();
		
	}

	Scene::~Scene()
	{
		
	}
	
	Entity Scene::CreateEntity(char* name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		NameComponent nameComponent = entity.AddComponent<NameComponent>(name);
		return entity;
	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for(auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}  
	}
}
