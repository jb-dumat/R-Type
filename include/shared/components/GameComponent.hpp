//
// EPITECH PROJECT, 2018
// GameComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <memory>
#include "ecs/Component.hpp"
#include "graphic/Window.hpp"

namespace rtype {
	class GameComponent : public ecs::Component {
	public:
		GameComponent(bool _isOver = true) : isOver(_isOver)
		{} 
	public:
		bool isOver;
	};
}