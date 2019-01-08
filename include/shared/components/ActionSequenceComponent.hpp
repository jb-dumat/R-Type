//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// MovementSequence Component
//

#pragma once

#include "ecs/Component.hpp"
#include "Action.hpp"

namespace rtype {
	class ActionSequenceComponent : public ecs::Component {
	public:
		ActionSequenceComponent(std::vector<Action> &_actions,
			size_t _currentAction = 0) :
		actions(_actions), currentAction(_currentAction)
		{}
	public:
		std::vector<Action> actions;
		size_t currentAction;
	};
}
