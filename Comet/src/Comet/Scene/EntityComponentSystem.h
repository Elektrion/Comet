#pragma once

#include <any>
#include <ranges>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "Comet/Core/Core.h"

namespace comet {

	class EntityComponentSystem {
	public:
		using entity_handle = uint32_t;
		static constexpr inline entity_handle null_entity = 0;
	private:
		template<typename T>
		using ComponentMap = std::unordered_map<entity_handle, Ref<T>>;
	public:
		constexpr entity_handle createEntity() {
			return ++entity_counter;
		}


		template<typename T, typename... Types>
		constexpr Ref<T> addComponent(entity_handle entity, Types&&... args) {
			auto [iter, b] = retrieveMapChecked<T>()->insert_or_assign(entity, createRef<T>(std::forward<Types>(args)...));
			return iter->second;
		}

		template<typename T>
		constexpr bool hasComponent(entity_handle entity) const {
			if(!component_maps.contains(typeid(T))) return false;
			return retrieveMapUnchecked<T>()->contains(entity);
		}

		template<typename T>
		constexpr Ref<T> getComponent(entity_handle entity) const {
			if(!component_maps.contains(typeid(T))) return nullptr;
			if(!retrieveMapUnchecked<T>()->contains(entity)) return nullptr;
			return retrieveMapUnchecked<T>()->at(entity);
		}

		template<typename T>
		constexpr void removeComponent(entity_handle entity) {
			if(!component_maps.contains(typeid(T))) return;
			auto map = retrieveMapUnchecked<T>();
			if(!map->contains(entity)) return;
			map->erase(entity);
		}


		constexpr auto getEntityView() const {
			return std::views::iota(entity_handle(1), entity_handle(entity_counter + 1));
		}

		template<typename T>
		constexpr auto getViewOf() {
			return *retrieveMapChecked<T>() | std::views::values;
		}
	private:
		template<typename T>
		constexpr const ComponentMap<T>* retrieveMapUnchecked() const {
			return std::any_cast<ComponentMap<T>>(&(component_maps.at(typeid(T))));
		}

		template<typename T>
		constexpr ComponentMap<T>* retrieveMapUnchecked() {
			return std::any_cast<ComponentMap<T>>(&(component_maps.at(typeid(T))));
		}

		template<typename T>
		constexpr ComponentMap<T>* retrieveMapChecked() {
			if(!component_maps.contains(typeid(T))) component_maps.emplace(typeid(T), std::make_any<ComponentMap<T>>());
			return std::any_cast<ComponentMap<T>>(&(component_maps.at(typeid(T))));
		}
	private:
		entity_handle entity_counter = 0;
		std::unordered_map<std::type_index, std::any> component_maps;
	};

	using ECS = EntityComponentSystem;

}
