//
// EPITECH PROJECT, 2018
// Rect2.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once
#include <iostream>

#include "Vec2.hpp"

namespace hutils {
	template <typename T>
	struct Rect2 {
		Rect2(Vec2<T> _pos = {}, Vec2<T> _size = {}) noexcept : pos(_pos), size(_size)
		{}
		Rect2(const Rect2 &) noexcept = default;
		Rect2 & operator=(const Rect2 &) noexcept = default;
		Rect2(Rect2 &&) noexcept = default;
		Rect2 & operator=(Rect2 &&) noexcept = default;

		bool operator==(const Rect2<T> & other)
		{
			return pos == other.pos && size == other.size;
		}

		bool operator!=(const Rect2<T> & other)
		{
			return !(*this == other);
		}

		Vec2<T> getCenter() const
		{
			return Vec2<T>(pos.x + size.x / 2, pos.y + size.y / 2);
		}

		bool intersects(const Rect2<T> &other) const
		{
			return (other.contains(pos) ||
				other.contains(pos.x + size.x, pos.y) ||
				other.contains(pos.x, pos.y + size.y) ||
				other.contains(pos.x + size.x, pos.y + size.y));
		}

		bool contains(const Vec2<T> &point) const
		{
			return (point.x >= pos.x && point.x <= pos.x + size.x &&
				point.y >= pos.y && point.y <= pos.y + size.y);
		}

		bool contains(T x, T y) const
		{
			return (x >= pos.x && x <= pos.x + size.x &&
				y >= pos.y && y <= pos.y + size.y);
		}

		Vec2<T> pos;
		Vec2<T> size;
	};

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Rect2<T> &r)
	{
		os << r.pos << " [" << r.size.x << ", " << r.size.y << "]";
		return os;
	}
}