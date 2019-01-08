//
// EPITECH PROJECT, 2018
// EventType.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <vector>
#include <memory>

namespace ecs {
	class ISystem;

	class Entity;

	struct Event {
		size_t type;
		std::vector<Entity> entities;
		std::shared_ptr<ISystem> emitterSystem;
	};
}