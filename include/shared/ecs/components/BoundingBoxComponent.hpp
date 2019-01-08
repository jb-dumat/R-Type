//
// EPITECH PROJECT, 2018
// BoundingBoxComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "ecs/Component.hpp"
#include "Rect2.hpp"
#include "Rect3.hpp"

namespace ecs {
	template <class Precision, size_t Dimension = 2>
	class BoundingBoxComponent : public Component {
	public:
		BoundingBoxComponent(hutils::Vec2<Precision> pos,
			hutils::Vec2<Precision> size) :
		box(hutils::Rect2<Precision>(pos, size)) {}
		hutils::Rect2<Precision> box;
	};

	template <class Precision>
	class BoundingBoxComponent<Precision, 3> : public Component {
	public:
		BoundingBoxComponent(hutils::Vec3<Precision> pos,
			hutils::Vec3<Precision> size) :
		box(hutils::Rect3<Precision>(pos, size)) {}
		hutils::Rect3<Precision> box;
	};
}