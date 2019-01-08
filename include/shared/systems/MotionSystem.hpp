//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Motion System
//

#pragma once

#include "ecs/System.hpp"
#include "components/MotionComponent.hpp"
#include "components/TransformComponent.hpp"

namespace rtype {
	class MotionSystem : public ecs::System {
  public:
    MotionSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager) {}

  public:

    void update(float dtime) final 
    {
      _ecsManager.forEachEntity<MotionComponent, TransformComponent>(
        [&](const ecs::Entity &, auto velocity, auto pos) {
          pos->x += velocity->x * velocity->speed * dtime;
          pos->y += velocity->y * velocity->speed * dtime;
        });
    }
  };
}