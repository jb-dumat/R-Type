//
// EPITECH PROJECT, 2018
// PlayerMovementSystem.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "ecs/System.hpp"
#include "GameEvent.hpp"
#include "components/MotionComponent.hpp"
#include "components/TransformComponent.hpp"

namespace rtype {
	class PlayerMovementSystem : public ecs::System {
	public:
		PlayerMovementSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager)
		{}
	public:
		void update(float deltaTime) final
		{
			auto events = _ecsManager.fetchEvents(GameEvent::PLAYER_MOVE);
			for (auto &it : events) {
				auto e = it.entities[0];
				auto mot = e.getComponent<MotionComponent>();
				auto pos = e.getComponent<TransformComponent>();
				pos->x += mot->x * mot->speed * deltaTime;
				pos->y += mot->y * mot->speed * deltaTime;
				// mot->x = 0;
				// mot->y = 0;
			}
		}
	};
}