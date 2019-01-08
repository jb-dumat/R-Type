//
// EPITECH PROJECT, 2018
// BulletComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "Vec2.hpp"
#include "ecs/Component.hpp"
#include "RType.hpp"

namespace rtype {
	class BulletComponent : public ecs::Component {
	public:
		BulletComponent(size_t _textureIdx, size_t _damage = 1,
			hutils::Vec2<float> _size = {0, 0}) :
		textureIdx(_textureIdx), damage(_damage), size(_size)
		{}
	public:
		size_t textureIdx;
		size_t damage;
		hutils::Vec2<float> size;

	};
}