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
		"./assets/actions/advancedMonster.action", "./assets/enemy3.png", 3, 3);
	monster->textureIdx = rtype::TEXTURE::ENEMY3;
	monster->bulletTextureIdx = rtype::TEXTURE::BULLET4;
	monster->bulletWidth = 100;
	monster->bulletHeight = 55;
	monster->width = 120;
	monster->height = 63;
	return (monster);
}