//
// EPITECH PROJECT, 2018
// ActionTriggerSystem.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <memory>
#include <iostream>
#include "Vec2.hpp"
#include "ecs/System.hpp"
#include "components/ActionSequenceComponent.hpp"
#include "components/MotionComponent.hpp"
#include "components/ElapsedTimeComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/MonsterComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/BulletComponent.hpp"
#include "components/BoundingBoxComponent.hpp"
#include "components/DamageComponent.hpp"

namespace rtype {
	class ActionTriggerSystem : public ecs::System {
	public:
		ActionTriggerSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager)
		{}
	public:
		void update(float) final
		{
			_ecsManager.forEachEntity<ActionSequenceComponent, ElapsedTimeComponent>(
				[&](const ecs::Entity &e, auto aCpn, auto tCpn) {
					if (aCpn->actions.size() < 1 ||
						tCpn->eTime < aCpn->actions[aCpn->currentAction].startAt)
						return;
					if (aCpn->actions[aCpn->currentAction].type == ActionType::ATTACK)
						_triggerAttackAction(e, aCpn->actions[aCpn->currentAction]);
					else if (aCpn->actions[aCpn->currentAction].type == ActionType::MOVE)
						_triggerMoveAction(e, aCpn->actions[aCpn->currentAction]);
					if (aCpn->currentAction >= aCpn->actions.size() - 1) {
						aCpn->currentAction = 0;
						tCpn->eTime = 0;
					} else
						aCpn->currentAction += 1;
				});
		}
	private:
		void _triggerAttackAction(const ecs::Entity &e, Action &action)
		{
			auto bullet = e.getComponent<BulletComponent>();
			auto pos = e.getComponent<TransformComponent>();
			if (!pos)
				return;
			bool isPlayer = e.getComponent<MonsterComponent>() == nullptr;
			_ecsManager.createEntity()
			.addComponent<SpriteComponent>(bullet ?
				bullet->textureIdx : size_t(TEXTURE::BULLET))
			.addComponent<TransformComponent>(pos->x, pos->y)
			.addComponent<BoundingBoxComponent>(hutils::Vec2<float>(pos->x, pos->y),
				bullet ? bullet->size : hutils::Vec2<float>(97, 48))
			.addComponent<DamageComponent>(bullet ? bullet->damage : 1, isPlayer)
			.addComponent<MotionComponent>(action.x, action.y, action.speed);
		}

		void _triggerMoveAction(const ecs::Entity &e, Action &action)
		{
			auto mot = e.getComponent<MotionComponent>();
			if (!mot)
				return;
			mot->x = action.x;
			mot->y = action.y;
			mot->speed = action.speed;
		}

	};
}