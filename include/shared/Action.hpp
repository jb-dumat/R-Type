//
// EPITECH PROJECT, 2018
// Action.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <iostream>

namespace rtype {
	namespace ActionType {
		enum {
			ATTACK = 0,
			MOVE
		};
	}

	class Action {
	public:
		Action() : type(ActionType::MOVE), startAt(0), x(0), y(0), speed(-1)
		{}
	public:
		size_t type;
		double startAt;
		float x;
		float y;
		float speed;
	public:
		friend std::ostream& operator<<(std::ostream &os, const Action &a)
		{
			std::vector<std::string> actionTypes({"Attack", "Move"});
			os << "Type: " << actionTypes[a.type] << std::endl;
			os << "Start at: " << a.startAt << "s" << std::endl;
			os << "Direction(x, y): " << a.x << ", " << a.y << std::endl;
			return os << "Speed: " << a.speed << std::endl;
		}
	};
}