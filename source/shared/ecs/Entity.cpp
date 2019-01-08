//
// EPITECH PROJECT, 2018
// Entity
// File description:
// Hung Dao Nguyen
//

#include "ecs/Entity.hpp"
#include "ecs/EntityManager.hpp"

namespace ecs {
	void Entity::remove() const
	{
		auto entityManager = _ecsManager.getEntityManager();
		entityManager->removeEntity(*this);
	}
}