//
// EPITECH PROJECT, 2018
// EcsManager
// File description:
// Hung Dao Nguyen
//

#include <exception>
#include "ecs/EcsManager.hpp"
#include "ecs/EntityManager.hpp"

namespace ecs {
	EcsManager::EcsManager() noexcept :
	_entityManager(std::make_shared<EntityManager>(*this)),
	_systemManager(std::make_shared<SystemManager>(*this)),
	_eventManager(std::make_shared<EventManager>(_systemManager))
	{}

	void EcsManager::update(float deltaTime)
	{
		_systemManager->update(deltaTime);
	}

	ecs::Entity EcsManager::createEntity()
	{
		return _entityManager->createEntity();
	}

	void EcsManager::removeEntityComponents(const Entity &entity)
	{
		for (auto &it : _componentManagers)
			it.second->removeComponent(entity);
	}

	Entity EcsManager::registerGameObject(size_t gameObjectKey)
	{
		auto entityModel = createEntity();
		_gameObjects.emplace(gameObjectKey, entityModel.id);
		_gameObjectsIds.emplace(entityModel.id);
		return entityModel;
	}

	Entity EcsManager::createGameObject(size_t gameObjectKey)
	{
		if (_gameObjects.find(gameObjectKey) == _gameObjects.end()) {
			std::cerr << "createGameObject: GameObjectKey not found." << std::endl;
			return createEntity();
		}
		auto entity = createEntity();
		auto entityModel = Entity(*this, _gameObjects[gameObjectKey]);
		for (auto &pair : _componentManagers)
			pair.second->dupComponent(entityModel, entity);
		return entity;
	}

	void EcsManager::clearEntities()
	{
		_entityManager->clearEntities();
	}
}