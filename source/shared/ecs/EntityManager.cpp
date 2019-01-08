//
// EPITECH PROJECT, 2018
// EntityManager
// File description:
// Hung Dao Nguyen
//

#include "ecs/Entity.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/EntityManager.hpp"

namespace ecs {
	EntityManager::EntityManager(EcsManager &ecsManager) noexcept :
	_lastId(0), _ecsManager(ecsManager)
	{}

	EntityManager::~EntityManager()
	{}

	ecs::Entity EntityManager::createEntity()
	{
		size_t id = _lastId;

		if (_availableIds.size() > 0) {
			id = _availableIds.back();
			_availableIds.pop_back();
		}
		ecs::Entity newEntity(_ecsManager, id);
		entities.insert(newEntity);
		_lastId += 1;
		return newEntity;
	}

	void EntityManager::removeEntity(const ecs::Entity &entity)
	{
		_availableIds.push_back(entity.id);
		_ecsManager.removeEntityComponents(entity);
		entities.erase(entity);
	}

	void EntityManager::clearEntities()
	{
		_lastId = 0;
		for (auto &it : entities) {
			it.remove();
			_ecsManager.removeEntityComponents(it);
		}
		_availableIds.clear();
		entities.clear();
	}
}
