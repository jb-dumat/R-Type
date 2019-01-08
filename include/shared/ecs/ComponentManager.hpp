//
// EPITECH PROJECT, 2018
// ComponentManager.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "IComponentManager.hpp"
#include "Entity.hpp"

namespace ecs {
	class Component;

	template <class T>
	class ComponentManager : public IComponentManager {
	public:
		ComponentManager(EcsManager &ecsManager) : _ecsManager(ecsManager) {}
		ComponentManager(const ComponentManager &) noexcept = delete;
		ComponentManager(ComponentManager &&) noexcept = delete;
		ComponentManager &operator=(ComponentManager &) noexcept = delete;
		ComponentManager &operator=(ComponentManager &&) noexcept = delete;
	public:
		template <class ...Args>
		std::shared_ptr<T> emplaceComponent(const Entity &ownerEntity, Args &&...args)
		{
			if (components.find(ownerEntity) != components.end()) {
				std::cerr
				<< "emplaceComponent: entity already has a component of the same type"
				<< std::endl;
				return nullptr;
			}
			components.emplace(ownerEntity, new T(std::forward<Args>(args)...));
			return components[ownerEntity];
		}

		void addComponent(const Entity &ownerEntity, T *component)
		{
			components.emplace(ownerEntity, component);
		}

		std::shared_ptr<T> getComponent(const Entity &ownerEntity)
		{
			if (components.find(ownerEntity) == components.end())
				return nullptr;
			return components[ownerEntity];
		}

		void removeComponent(const Entity &ownerEntity) final
		{
			if (components.find(ownerEntity) == components.end())
				return;
			components.erase(ownerEntity);
		}

		void dupComponent(const Entity &owner, const Entity &newOwner) final
		{
			if (components.find(owner) == components.end()
				|| components.find(newOwner) != components.end())
				return;
			auto component = components[owner].get();
			components.emplace(newOwner, new T(*component));
		}

		size_t countComponents()
		{
			return components.size();
		}
	public:
		std::unordered_map<Entity, std::shared_ptr<T>> components;
	private:
		EcsManager &_ecsManager;
	};
}