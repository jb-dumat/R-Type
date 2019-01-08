//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Life Time Component
//

#pragma once

#include "ecs/Component.hpp"

namespace rtype {
  struct LifeTimeComponent : public ecs::Component {
    LifeTimeComponent(double _lTime) : lTime(_lTime) {}

    double lTime;
  };
}
