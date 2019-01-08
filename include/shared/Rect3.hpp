//
// EPITECH PROJECT, 2018
// Rect3.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <iostream>

#include "Vec3.hpp"

namespace hutils {
	template <typename T>
	struct Rect3 {
		Rect3(Vec3<T> _pos = {}, Vec3<T> _size = {}) noexcept : pos(_pos), size(_size)
		{}
		Rect3(const Rect3 &) noexcept = default;
		Rect3 & operator=(const Rect3 &) noexcept = default;
		Rect3(Rect3 &&) noexcept = default;
		Rect3 & operator=(Rect3 &&) noexcept = default;

		bool operator==(const Rect3<T> & other)
		{
			return pos == other.pos && size == other.size;
		}

		bool operator!=(const Rect3<T> & other)
		{
			return !(*this == other);
		}

		Vec3<T> getCenter() const
		{
			return Vec3<T>(pos.x + size.x / 2, pos.y + size.y / 2);
		}

		bool intersects(const Rect3<T> &other) const
		{
			return (other.contains(pos) ||
				other.contains(pos.x + size.x, pos.y, pos.z) ||
				other.contains(pos.x, pos.y + size.y, pos.z) ||
				other.contains(pos.x, pos.y, pos.z + size.z) ||
				other.contains(pos.x, pos.y + size.y, pos.z + size.z) ||
				other.contains(pos.x + size.x, pos.y, pos.z + size.z) ||
				other.contains(pos.x + size.x, pos.y + size.y, pos.z) ||
				other.contains(pos.x + size.x, pos.y + size.y, pos.z + size.z));
		}

		bool contains(const Vec3<T> &point) const
		{
			return (point.x >= pos.x && point.x <= pos.x + size.x &&
				point.y >= pos.y && point.y <= pos.y + size.y &&
				point.z >= pos.z && point.z <= pos.z + size.z);
		}

		bool contains(T x, T y, T z) const
		{
			return (x >= pos.x && x <= pos.x + size.x &&
				y >= pos.y && y <= pos.y + size.y &&
				z >= pos.z && z <= pos.z + size.z);
		}

		Vec3<T> pos;
		Vec3<T> size;
	};

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Rect3<T> &r)  
	{  
		os << r.pos << " [" << r.size.x << ", " << r.size.y << ", " << r.size.z << "]";
		return os;
	}
}