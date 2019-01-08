//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Elapsed Time Component
//

#pragma once

#include "ecs/Component.hpp"

namespace rtype {
  struct ElapsedTimeComponent : public ecs::Component {
    ElapsedTimeComponent(double _eTime = 0) : eTime(_eTime) {}

    double eTime;
  };
}
