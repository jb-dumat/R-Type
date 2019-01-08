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
		"./assets/actions/simpleMonster.action", "./assets/enemy1.png", 1, 1);
	monster->textureIdx = rtype::TEXTURE::ENEMY;
	monster->bulletTextureIdx = rtype::TEXTURE::BULLET2;
	monster->bulletWidth = 42;
	monster->bulletHeight = 42;
	monster->width = 85;
	monster->height = 48;
	return (monster);
}