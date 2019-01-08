//
// EPITECH PROJECT, 2018
// MotionComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "ecs/Component.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"

namespace ecs {
	template <class Precision, size_t Dimension = 2>
	class MotionComponent : public Component {
	public:
		MotionComponent(Precision _x, Precision _y, Precision _speed) :
		x(_x), y(_y), speed(_speed) {}
		MotionComponent(hutils::Vec2<Precision> pos, Precision _speed) :
		x(pos.x), y(pos.y), speed(_speed) {}
		Precision x;
		Precision y;
		Precision speed;
	};

	template <class Precision>
	class MotionComponent<Precision, 3> : public Component {
	public:
		MotionComponent(Precision _x, Precision _y, Precision _z, Precision _speed) :
		x(_x), y(_y), z(_z), speed(_speed) {}
		MotionComponent(hutils::Vec3<Precision> pos, Precision _speed) :
		x(pos.x), y(pos.y), z(pos.z), speed(_speed) {}
		Precision x;
		Precision y;
		Precision z;
		Precision speed;
	};
}