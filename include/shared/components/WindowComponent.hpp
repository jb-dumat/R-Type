//
// EPITECH PROJECT, 2018
// WindowComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <memory>
#include "ecs/Component.hpp"
#include "graphic/Window.hpp"

namespace rtype {
	class WindowComponent : public ecs::Component {
	public:
		WindowComponent(size_t w, size_t h, const std::string &title) :
		window(std::make_shared<graphic::Window>(w, h, title)) {}
	public:
		std::shared_ptr<graphic::Window> window;
	};
}