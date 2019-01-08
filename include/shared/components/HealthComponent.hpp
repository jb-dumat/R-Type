//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Health Component
//

#pragma once

#include "ecs/Component.hpp"

namespace rtype {
  struct HealthComponent : public ecs::Component {
    HealthComponent(int _hp) : hp(_hp) {}

    int hp;
  };
}
