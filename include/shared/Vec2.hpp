//
// EPITECH PROJECT, 2018
// Vec2.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <iostream>

namespace hutils {
	template <typename T>
	struct Vec2 {
		Vec2(T _x = 0, T _y = 0) noexcept : x(_x), y(_y)
		{}
		Vec2(const Vec2 &) noexcept = default;
		Vec2 &operator=(const Vec2 &) noexcept = default;
		Vec2(Vec2 &&) noexcept = default;
		Vec2 &operator=(Vec2 &&) noexcept = default;

		bool operator==(const Vec2<T> &other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Vec2<T> &other)
		{
			return !(*this == other);
		}

		friend std::ostream& operator<<(std::ostream& os, const Vec2<T> &v)  
		{  
			return os << "(" << v.x << ", " << v.y << ")";
		}

		T x;
		T y;
	};

}