//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Controller Component
//

#pragma once

#include <functional>
#include "ecs/Component.hpp"
#include "ecs/ComponentManager.hpp"
#include "IEvent.hpp"
#include "Window.hpp"

namespace rtype {
	struct ControllerComponent : public ecs::Component {
		ControllerComponent(std::function<void(const graphic::EventResult &,
			const ecs::Entity &, ecs::EcsManager &)> _onInput) :
		onInput(_onInput) {}

		std::function<void(const graphic::EventResult &,
			const ecs::Entity &, ecs::EcsManager &)> onInput;
	};
}
