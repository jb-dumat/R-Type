//
// EPITECH PROJECT, 2018
// RoomComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <memory>
#include <list>
#include "Player.hpp"
#include "ecs/Component.hpp"
#include "graphic/Window.hpp"
#include "components/MonsterComponent.hpp"

namespace rtype {
	class RoomComponent : public ecs::Component {
	public:
		RoomComponent(std::shared_ptr<std::list<std::shared_ptr<Player>>> _players,
			std::shared_ptr<std::vector<std::shared_ptr<MonsterComponent>>> _monsters,
			States _state) :
		players(_players), monsters(_monsters), state(_state)
		{} 
	public:
		std::shared_ptr<std::list<std::shared_ptr<Player>>> players;
		std::shared_ptr<std::vector<std::shared_ptr<MonsterComponent>>> monsters;
		States state;
		float spawnRate;
		size_t windowWidth;
		size_t windowHeight;
		int minMonster;
		int maxMonster;
	};
}