//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Motion System
//

#pragma once

#include "ecs/System.hpp"
#include "RType.hpp"
#include "components/BoundingBoxComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/PlayerComponent.hpp"

namespace rtype {
	class CollisionSystem : public ecs::System {
  public:
    CollisionSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager) {}

  public:

    void update(float) final 
    {
      _handlePlayerCollision();
      _ecsManager.forEachEntity<BoundingBoxComponent, TransformComponent>(
        [&](const ecs::Entity &e1, auto box1, auto pos1) {
          _ecsManager.forEachEntity<BoundingBoxComponent, TransformComponent>(
            [&](const ecs::Entity &e2, auto box2, auto pos2) {
              if (e1 == e2)
                return;
              box1->box.pos = hutils::Vec2<float>(pos1->x, pos1->y);
              box2->box.pos = hutils::Vec2<float>(pos2->x, pos2->y);
              if (box1->box.intersects(box2->box))
                _notifyCollision(e1, e2);
            });          
        });
    }
  private:
    void _notifyCollision(const ecs::Entity &e1, const ecs::Entity &e2)
    {
      emitEvent(this, GameEvent::COLLISION, {e1, e2});
    }

    void _handlePlayerCollision()
    {
      _ecsManager.forEachEntity<PlayerComponent, TransformComponent>(
        [&](const ecs::Entity &, auto, auto pos) {
          if (pos->x < 0)
            pos->x = 0;
          else if (pos->x > rtype::WINDOW_WIDTH)
            pos->x = rtype::WINDOW_WIDTH;
          if (pos->y < 0)
            pos->y = 0;
          else if (pos->y > rtype::WINDOW_HEIGHT)
            pos->y = rtype::WINDOW_HEIGHT;
        });
    }
  };
}