//
// EPITECH PROJECT, 2018
// IComponentManager.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

namespace ecs {
	class Entity;

	class IComponentManager {
	public:
		virtual void removeComponent(const Entity &ownerEntity) = 0;
		virtual void dupComponent(const Entity &owner, const Entity &newOwner) = 0;
	};
}