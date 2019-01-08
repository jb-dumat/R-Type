//
// EPITECH PROJECT, 2018
// Component.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

namespace ecs {
	class Component {
	public:
		Component() noexcept = default;
		~Component() noexcept = default;
		Component(const Component &) noexcept = default;
		Component(Component &&) noexcept = default;
		Component &operator=(Component &) noexcept = default;
		Component &operator=(Component &&) noexcept = default;
	};
}