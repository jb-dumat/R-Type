//
// EPITECH PROJECT, 2018
// SystemManager
// File description:
// Hung Dao Nguyen
//

#include "ecs/Entity.hpp"

namespace ecs {
	void SystemManager::update(float deltaTime)
	{
		auto eventManager = _ecsManager.getEventManager();
		for (auto &it : _systems) {
			// remove all events that were emitted by the current system
			eventManager->removeSystemEvents(it.second);
			it.second->update(deltaTime);
		}
		for (auto &it : _systemsToRemove)
			_systems.erase(it);
		_systemsToRemove.clear();
	}
}