//
// EPITECH PROJECT, 2018
// SimpleSimpleMonsterComponent.hpp
// File description:
// Hung Dao Nguyen
//

#include <memory>
#include "components/MonsterComponent.hpp"

extern "C" std::shared_ptr<rtype::MonsterComponent> getMonster()
{
	auto monster = std::make_shared<rtype::MonsterComponent>(
		"./assets/actions/simpleAsteroid.action", "./assets/asteroid.png", 2, 2);
	monster->textureIdx = rtype::TEXTURE::ASTEROID;
	monster->width = 50;
	monster->height = 50;
	return (monster);
}