//
// EPITECH PROJECT, 2018
// EventManager.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <initializer_list>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include "Event.hpp"

namespace ecs {
	class ISystem;

	class EventManager {
	public:
		EventManager(std::shared_ptr<SystemManager> systemManager) noexcept :
		_systemManager(systemManager) {};
		EventManager(const EventManager &) noexcept = delete;
		EventManager(EventManager &&) noexcept = delete;
		EventManager &operator=(EventManager &) noexcept = delete;
		EventManager &operator=(EventManager &&) noexcept = delete;
	public:
		template <class T>
		void addEvent(size_t eventType, std::initializer_list<Entity> entities)
		{
			auto isystem = _systemManager->getSystem<T>();
			if (isystem == nullptr)
				return;
			if (_events.find(isystem) == _events.end()) {
				_events.emplace(isystem, std::vector<Event>());
			}
			_events[isystem].push_back({eventType, entities, isystem});
		}
		void removeSystemEvents(std::shared_ptr<ISystem> emitterSystem);

		template <class... Args>
		std::vector<Event> fetchEvents(Args && ...args)
		{
			std::unordered_set<size_t> eventsTypes = {std::forward<Args>(args)...};
			std::vector<Event> events;
			for (auto &it : _events) {
				for (auto &event : it.second) {
					if (eventsTypes.find(event.type) != eventsTypes.end()) {
						events.push_back(event);
					}
				}
			}
			return events;
		}
	private:
		std::unordered_map<std::shared_ptr<ISystem>, std::vector<Event>> _events;
		std::shared_ptr<SystemManager> _systemManager;
	};
}