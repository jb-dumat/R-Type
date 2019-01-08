//
// EPITECH PROJECT, 2018
// EcsManager.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <typeindex>
#include <unordered_map>
#include <functional>
#include <memory>
#include <algorithm>
#include "IComponentManager.hpp"
#include "SystemManager.hpp"
#include "EventManager.hpp"

namespace ecs {
	template <class T>
	class ComponentManager;

	class EntityManager;

	class Component;

	using GameObject = Entity;

	class EcsManager {
	public:
		EcsManager() noexcept;
		~EcsManager() {}
		EcsManager(const EcsManager &) noexcept = delete;
		EcsManager(EcsManager &&) noexcept = delete;
		EcsManager &operator=(EcsManager &) noexcept = delete;
		EcsManager &operator=(EcsManager &&) noexcept = delete;
	public:
		void update(float deltaTime = 0);
		void removeEntityComponents(const Entity &entity);
		Entity createEntity();
		GameObject registerGameObject(size_t gameObjectKey);
		GameObject createGameObject(size_t gameObjectKey);
		template<class T>
		void emitEvent(size_t eventType, std::initializer_list<Entity> entities = {})
		{
			_eventManager->addEvent<T>(eventType, entities);
		}
	public:
		std::shared_ptr<EntityManager> getEntityManager()
		{
			return _entityManager;
		}

		std::shared_ptr<SystemManager> getSystemManager()
		{
			return _systemManager;
		}

		std::shared_ptr<EventManager> getEventManager()
		{
			return _eventManager;
		}

		template<class T>
		ComponentManager<T> *getComponentManager()
		{
			auto typei = std::type_index(typeid(T));
			if (_componentManagers.find(typei) == _componentManagers.end()) {
				_componentManagers[typei] = std::make_shared<ComponentManager<T>>(*this);
			}
			return static_cast<ComponentManager<T> *>(_componentManagers[typei].get());
		}
	public:
		template <class... Args>
		std::vector<Event> fetchEvents(Args && ...args)
		{
			return _eventManager->fetchEvents(std::forward<Args>(args)...);
		}

		template <class Func, class ...Args>
		void forEachEntity(Func &&func, Args &&...args);

		template <class ComponentType, class Func, class ...Args>
		void forEachEntity(Func &&func, Args &&...args)
		{
			static_assert(std::is_base_of<Component, ComponentType>::value,
				"forEachEntiy: received template parameter is not a component.");
			auto componentMgr = getComponentManager<ComponentType>();
			if (!componentMgr)
				return;
			for (auto &pair : componentMgr->components) {
				if (_gameObjectsIds.find(pair.first.id) != _gameObjectsIds.end())
					continue;
				std::invoke(std::forward<Func>(func),
					pair.first, pair.second, std::forward<Args>(args)...);
			}
		}

		template <class ComponentType, class ComponentType2, class Func, class ...Args>
		void forEachEntity(Func &&func, Args &&...args)
		{
			static_assert(std::is_base_of<Component, ComponentType2>::value,
				"forEachEntiy: received template parameter is not a component.");
			auto componentMgr2 = getComponentManager<ComponentType2>();
			if (!componentMgr2)
				return;
			forEachEntity<ComponentType>([&](const Entity &e, auto component) {
				auto component2 = componentMgr2->components[e];
				if (component2 == nullptr)
					return;
				std::invoke(std::forward<Func>(func),
					e, component, component2, std::forward<Args>(args)...);
			});
		}

		template <class ComponentType, class ComponentType2, class ComponentType3,
		class Func, class ...Args>
		void forEachEntity(Func &&func, Args &&...args)
		{
			static_assert(std::is_base_of<Component, ComponentType3>::value,
				"forEachEntiy: received template parameter is not a component.");
			auto componentMgr3 = getComponentManager<ComponentType3>();
			if (!componentMgr3)
				return;
			forEachEntity<ComponentType, ComponentType2>(
				[&](const Entity &e, auto component, auto component2) {
					auto component3 = componentMgr3->components[e];
					if (component3 == nullptr)
						return;
					std::invoke(std::forward<Func>(func),
						e, component, component2, component3,
						std::forward<Args>(args)...);
				});
		}

		void clearEntities();
	private:
		std::shared_ptr<EntityManager> _entityManager;
		std::shared_ptr<SystemManager> _systemManager;
		std::unordered_map<std::type_index,
		std::shared_ptr<IComponentManager>> _componentManagers;
		std::shared_ptr<EventManager> _eventManager;
		std::unordered_set<size_t> _gameObjectsIds;
		std::unordered_map<size_t, size_t> _gameObjects;
	};
}