#include "fepch.h"
#include "Entity.h"

namespace FoxEngine
{
	Entity::Entity(entt::entity entity, Scene* scene)
		:m_Entity(entity), m_Scene(scene){
		
	}
}
