//
// EPITECH PROJECT, 2018
// SpawnMonsterSystem.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "ecs/System.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Entity.hpp"
#include "Utilities.hpp"
#include "GameEvent.hpp"
#include "components/RoomComponent.hpp"
#include "components/MotionComponent.hpp"
#include "components/ActionSequenceComponent.hpp"
#include "components/ElapsedTimeComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/BulletComponent.hpp"
#include "components/MonsterComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/DamageComponent.hpp"
#include "components/BoundingBoxComponent.hpp"

namespace rtype {
	class SpawnMonsterSystem : public ecs::System {
	public:
		SpawnMonsterSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager),
		_nbMonsters(0)
		{}
	public:
		void update(float) final
		{
			_monsterCounter();
			_ecsManager.forEachEntity<RoomComponent>(
				[&](const ecs::Entity &, auto room){
					_room = room;
				});
			if (!_room)
				return;
	//		std::cout << _room->monsters->size() << std::endl;
			auto randnb = hutils::randInt(0, FRAME_RATE / _room->spawnRate);
			if ((_nbMonsters < _room->minMonster || randnb == 0)
				&& _room->monsters->size() > 0 && _nbMonsters < _room->maxMonster)
				_spawnMonster();
		}
	private:
		void _spawnMonster()
		{
			_nbMonsters += 1;
			auto monsterIdx = hutils::randInt(0, _room->monsters->size() - 1);
			auto monster = (*_room->monsters)[monsterIdx];
			auto y = hutils::randInt(0, _room->windowHeight - 100);
			_ecsManager.createEntity()
			.addComponent<SpriteComponent>(monster->textureIdx)
			.addComponent<TransformComponent>(_room->windowWidth, y)
			.addComponent<BoundingBoxComponent>(hutils::Vec2<float>(_room->windowWidth, y), 
				hutils::Vec2<float>(monster->width, monster->height))
			.addComponent<MotionComponent>(0, 0, monster->speed)
			.addComponent<ElapsedTimeComponent>()
			.addComponent<HealthComponent>(monster->hp)
			.addComponent<DamageComponent>(monster->damage, false)
			.addComponent<ActionSequenceComponent>(monster->actions)
			.addComponent<BulletComponent>(monster->bulletTextureIdx, monster->damage,
				hutils::Vec2<float>(monster->bulletWidth, monster->bulletHeight))
			.addComponent<MonsterComponent>();
		}

		void _monsterCounter()
		{
			auto events = _ecsManager.fetchEvents(GameEvent::MONSTER_DEAD);
			_nbMonsters -= events.size();
		}
	private:
		std::shared_ptr<RoomComponent> _room;
		int _nbMonsters;
	};
}