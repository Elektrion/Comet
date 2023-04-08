#include "cmt_pch.h"
#include "Scene.h"

#include "Comet/Renderer/RenderCommand.h"
#include "Comet/Renderer/Renderer2D.h"

#include "Comet/Scene/Components.h"
#include "Comet/Scene/OrthographicCameraController.h"

namespace comet {
    Ref<Scene> Scene::createScene() {
        return createRef<Scene>();
    }

    Entity Scene::createEntity() {
        return { ecs.createEntity(), this };
    }

    void Scene::onUpdate(Timestep dt) {
        RenderCommand::setClearColor(background_color.r, background_color.g, background_color.b);
        RenderCommand::clear();
        Renderer2D::beginScene(scene_camera);

        for(auto entity : getEntities()) {
            if(auto transform = entity.getComponent<components::Transform>())
                if(auto sprite = entity.getComponent<components::Sprite>())
                    if(sprite->texture)
                        Renderer2D::drawQuad(transform->position, transform->scale, transform->rotation.z, sprite->texture, sprite->color);
                    else
                        Renderer2D::drawQuad(transform->position, transform->scale, transform->rotation.z, sprite->color);
            if(auto camera_controller = entity.getComponent<OrthographicCameraController>())
                camera_controller->onUpdate(dt);
        }

        Renderer2D::endScene();
    }

    void Scene::onEvent(Event& e) {
        for(const auto& controller : ecs.getViewOf<OrthographicCameraController>())
            controller->onEvent(e);
    }

}
