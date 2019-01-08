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
#include "components/StarComponent.hpp"

namespace rtype {
	class StarfieldSystem : public ecs::System {
  public:
    StarfieldSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager) {}

  public:

    void update(float) final 
    {
      _ecsManager.forEachEntity<StarComponent, TransformComponent>(
        [&](const ecs::Entity &, auto, auto pos) {
          if (pos->x < -20) {
            auto x = hutils::randInt(0, 100);
            auto y = hutils::randInt(0, rtype::WINDOW_HEIGHT);
            pos->x = rtype::WINDOW_WIDTH + x;
            pos->y = y;
          }
        });
    }
  };
}