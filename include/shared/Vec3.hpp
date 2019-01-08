//
// EPITECH PROJECT, 2018
// Vec3.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <iostream>

namespace hutils {
	template <typename T>
	struct Vec3 {
		Vec3(T _x = 0, T _y = 0, T _z = 0) noexcept : x(_x), y(_y), z(_z)
		{}
		Vec3(const Vec3 &) noexcept = default;
		Vec3 & operator=(const Vec3 &) noexcept = default;
		Vec3(Vec3 &&) noexcept = default;
		Vec3 & operator=(Vec3 &&) noexcept = default;

		bool operator==(const Vec3<T> & other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(const Vec3<T> & other)
		{
			return !(*this == other);
		}

		friend std::ostream& operator<<(std::ostream& os, const Vec3<T> &v)  
		{  
			return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		}

		T x;
		T y;
		T z;
	};

}