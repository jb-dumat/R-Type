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
		"./assets/actions/basicMonster.action", "./assets/enemy2.png", 2, 2);
	monster->textureIdx = rtype::TEXTURE::ENEMY2;
	monster->bulletTextureIdx = rtype::TEXTURE::BULLET3;
	monster->bulletWidth = 67;
	monster->bulletHeight = 42;
	monster->width = 100;
	monster->height = 53;
	return (monster);
}