#pragma once

#include <ranges>

#include "Comet/Core/Math.h"
#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"

#include "Comet/Renderer/Camera.h"

#include "Comet/Scene/EntityComponentSystem.h"

namespace comet {

	class Scene {
	public:
		static Ref<Scene> createScene();
	public:
		class Entity createEntity();
		constexpr auto getEntities();

		constexpr void setBackgroundColor(float r, float g, float b) {
			background_color = { r, g, b, 1.0f };
		}

		void setCamera(Ref<Camera> camera) {
			scene_camera = camera;
		}

		void onUpdate(Timestep dt);
		void onEvent(Event& e);
	private:
		EntityComponentSystem ecs{};
		glm::vec4 background_color{ 0.0f, 0.0f, 0.0f, 1.0f };
		Ref<Camera> scene_camera = nullptr;

		friend class Entity;
	};

	class Entity {
	public:
		constexpr Entity(ECS::entity_handle handle, Scene* const scene) : handle{ handle }, scene{ scene } {}

		constexpr ECS::entity_handle getHandle() const {
			return handle;
		}

		template<typename T, typename... Types>
		constexpr Ref<T> addComponent(Types&&... args) {
			return scene->ecs.addComponent<T>(handle, std::forward<Types&&>(args)...);
		}

		template<typename T, typename... Types>
		constexpr Entity& chainAddComponent(Types&&... args) {
			this->addComponent<T>(std::forward<Types&&>(args)...);
			return *this;
		}

		template<typename T>
		constexpr bool hasComponent() const {
			return scene->ecs.hasComponent<T>(handle);
		}

		template<typename T>
		constexpr Ref<T> getComponent() const {
			return scene->ecs.getComponent<T>(handle);
		}

		template<typename T>
		constexpr void removeComponent() {
			scene->ecs.removeComponent<T>(handle);
		}
	private:
		ECS::entity_handle handle;
		Scene* scene;
	};

	constexpr auto Scene::getEntities() {
		return ecs.getEntityView() | std::views::transform([this](const auto& entity_handle) { return Entity{ entity_handle, this }; });
	}

}
