#include "fepch.h"
#include "FoxEngine/Scene/Scene.h"

#include "Components.h"
#include "FoxEngine/Renderer/Renderer2D.h"
#include "FoxEngine/Renderer/Camera.h"

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
	    Camera* mainCamera = nullptr;
	    glm::mat4* cameraTransform = nullptr;
        {
            auto view = registry.view<TransformComponent, CameraComponent>();
            for (auto& entity : view) {
                auto&[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
                if(camera.primary){
                    mainCamera = &camera.camera;
                    cameraTransform = &transform.transform;
                    break;
                }
            }
        }

        if(mainCamera){
            Renderer2D::beginScene(mainCamera->getProjection(), *cameraTransform);

            auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for(auto entity : group)
            {
                auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::drawQuad(transform, sprite.color);
            }
            Renderer2D::endScene();
        }
	}

    void Scene::onViewportResize(uint32_t width, uint32_t height) {
        viewportWidth = width;
        viewportHeight = height;

        auto view = registry.view<CameraComponent>();
        for (auto& entity : view) {
            auto& camera = view.get<CameraComponent>(entity);
            if(!camera.fixedAspectRatio){
                camera.camera.setViewportSize(width, height);
            }
        }
    }

}
