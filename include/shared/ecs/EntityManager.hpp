//
// EPITECH PROJECT, 2018
// EntityManager.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <unordered_set>
#include <vector>
#include "Entity.hpp"

namespace ecs {
	class EcsManager;

	class EntityManager {
	public:
		EntityManager(EcsManager &ecsManager) noexcept;
		~EntityManager();
		EntityManager(const EntityManager &) noexcept = delete;
		EntityManager(EntityManager &&) noexcept = delete;
		EntityManager &operator=(EntityManager &) noexcept = delete;
		EntityManager &operator=(EntityManager &&) noexcept = delete;
	public:
		ecs::Entity createEntity();
		void removeEntity(const ecs::Entity &entity);
		void clearEntities();
	public:
		std::unordered_set<Entity> entities;
	private:
		size_t _lastId;
		std::vector<size_t> _availableIds;
		EcsManager &_ecsManager;
	};

	template <class Func, class ...Args>
	void EcsManager::forEachEntity(Func &&func, Args &&...args)
	{
		for (auto &it : _entityManager->entities) {
			if (_gameObjectsIds.find(it.id) != _gameObjectsIds.end())
				continue;
			std::invoke(std::forward<Func>(func), it, std::forward<Args>(args)...);
		}
	}
}