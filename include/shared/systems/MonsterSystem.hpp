//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Motion System
//

#pragma once

#include "ecs/System.hpp"
#include "GameEvent.hpp"
#include "components/MonsterComponent.hpp"

namespace rtype {
	class MonsterSystem : public ecs::System {
  public:
    MonsterSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager) {}

  public:

    void update(float) final 
    {
      auto events = _ecsManager.fetchEvents(GameEvent::DEAD);
      for (auto &it : events) {
        auto e = it.entities[0];
        if (e.getComponent<MonsterComponent>() != nullptr) {
          emitEvent(this, GameEvent::MONSTER_DEAD, {e});
          e.remove();
        }
      }
    }
  };
}