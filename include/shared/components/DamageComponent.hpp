//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Damage Component
//

#pragma once

#include "ecs/Component.hpp"
#include <cstddef>

namespace rtype {
  struct DamageComponent : public ecs::Component {
    DamageComponent(std::size_t _damage, bool _isplayer = false) :
    damage(_damage), isdmgToMonster(_isplayer) {}

    std::size_t damage;
    bool isdmgToMonster;
  };
}