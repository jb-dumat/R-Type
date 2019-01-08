//
// EPITECH PROJECT, 2018
// TransformComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "ecs/Component.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"

namespace ecs {
	template <class Precision, size_t Dimension = 2>
	class TransformComponent : public Component {
	public:
		TransformComponent(Precision _x, Precision _y) :
		x(_x), y(_y) {}
		TransformComponent(hutils::Vec2<Precision> pos) :
		x(pos.x), y(pos.y) {}
		Precision x;
		Precision y;
	};

	template <class Precision>
	class TransformComponent<Precision, 3> : public Component {
	public:
		TransformComponent(Precision _x, Precision _y, Precision _z) :
		x(_x), y(_y), z(_z) {}
		TransformComponent(hutils::Vec3<Precision> pos) :
		x(pos.x), y(pos.y), z(pos.z) {}
		Precision x;
		Precision y;
		Precision z;
	};
}