//
// EPITECH PROJECT, 2018
// EventManager
// File description:
// Hung Dao Nguyen
//

#include "ecs/Entity.hpp"

namespace ecs {
	void EventManager::removeSystemEvents(std::shared_ptr<ISystem> emitterSystem)
	{
		if (_events.find(emitterSystem) != _events.end()
			&& _events[emitterSystem].size() > 0) {
			_events[emitterSystem].clear();
		}
	}
}