//
// EPITECH PROJECT, 2018
// ServerComSystem.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "ecs/System.hpp"
#include "Vec2.hpp"
#include "GameEvent.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/RoomComponent.hpp"

namespace rtype {
	class ServerComSystem : public ecs::System {
	public:
		ServerComSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager)
		{}
	public:
		void update(float) final
		{
			_ecsManager.forEachEntity<RoomComponent>(
				[&](const ecs::Entity &, auto room){
					_room = room;
				});
			if (!_room)
				return;
			_updatePlayers();
			_handleGameOver();
		}
	private:
		void _handleGameOver()
		{
			auto events = _ecsManager.fetchEvents(GameEvent::GAMEOVER);
			if (events.size() < 1)
				return;
			for (auto &it : *_room->players) {
				auto p = Serializer::makeRequest(
					Serializer::makePayload(RequestID::UDP_GAME_OVER));
				if (it->usocket)
					it->usocket->send(p.first, p.second);
			}
		}

		void _updatePlayers()
		{
			_ecsManager.forEachEntity<SpriteComponent, TransformComponent>(
				[&](const ecs::Entity &e, auto sprC, auto posC) {
					for (auto &it : *_room->players) {
						auto p = Serializer::makeRequest(
							Serializer::makePayload(RequestID::UDP_SEND_ENTITY, e.id, 
								sprC->textureId, posC->x, posC->y));
						if (it->usocket)
							it->usocket->send(p.first, p.second);
					}
				});
		}
	private:
		std::shared_ptr<RoomComponent> _room;
	};
}