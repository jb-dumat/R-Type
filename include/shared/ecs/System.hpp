//
// EPITECH PROJECT, 2018
// System.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <initializer_list>
#include "ISystem.hpp"
#include "EcsManager.hpp"
#include "EventManager.hpp"

namespace ecs {
	class System : public ISystem {
	public:
		System(EcsManager &ecsManager) : _ecsManager(ecsManager) {}
		System(const System &) noexcept = delete;
		System(System &&) noexcept = delete;
		System &operator=(System &) noexcept = delete;
		System &operator=(System &&) noexcept = delete;
	public:
		virtual void update(float) override {}
	protected:
		template <class T>
		void emitEvent(T *, size_t eventType, std::initializer_list<Entity> entities = {})
		{
			auto eventManager = _ecsManager.getEventManager();
			eventManager->addEvent<T>(eventType, entities);
		}

	protected:
		EcsManager &_ecsManager;
	};
}