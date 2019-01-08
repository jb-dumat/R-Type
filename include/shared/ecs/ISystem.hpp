//
// EPITECH PROJECT, 2018
// ISystem.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

namespace ecs {
	class ISystem {
	public:
		virtual void update(float deltaTime) = 0;
	};
}