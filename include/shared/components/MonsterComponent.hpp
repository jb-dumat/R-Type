//
// EPITECH PROJECT, 2018
// MonsterComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <string>
#include <vector>
#include "ecs/Component.hpp"
#include "RType.hpp"

namespace rtype {
	class MonsterComponent : public ecs::Component {
	public:
		MonsterComponent(const std::string &_actionFile = "",
			const std::string &_textureFile = "",
			size_t _damage = 0, size_t _hp = 0) :
		actionFile(_actionFile), textureFile(_textureFile),
		speed(1), damage(_damage), hp(_hp), bulletTextureIdx(TEXTURE::BULLET2),
		actions(rtype::parseActions(_actionFile))
		{}
	public:
		std::string actionFile;
		std::string textureFile;
		std::string bulletTextureFile;
		float speed;
		size_t damage;
		size_t hp;
		size_t textureIdx;
		size_t bulletTextureIdx;
		float bulletWidth;
		float bulletHeight;
		float width;
		float height;
		std::vector<Action> actions;
	};
}