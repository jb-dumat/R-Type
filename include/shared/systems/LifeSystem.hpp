//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Life System
//

#pragma once

#include "ecs/System.hpp"
#include "components/HealthComponent.hpp"
#include "components/DamageComponent.hpp"
#include "GameEvent.hpp"
#include "ecs/Entity.hpp"

namespace rtype {
	class LifeSystem : public ecs::System {
  public:
    LifeSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager) {}
  
  public:
    void update(float) final
    {
      handleCollisionEvents();
    }

  private:
    void handleCollisionEvents()
    {
      auto eventManager = _ecsManager.getEventManager();
      auto events = eventManager->fetchEvents(GameEvent::COLLISION);

      for (auto &it : events) {
        auto firstElem = it.entities[0];
        auto secondElem = it.entities[1];
        std::shared_ptr<DamageComponent> dmgF = firstElem.getComponent<DamageComponent>();
        std::shared_ptr<DamageComponent> dmgS = secondElem.getComponent<DamageComponent>();
        std::shared_ptr<rtype::HealthComponent> hp = firstElem.getComponent<HealthComponent>();
        if (hp && dmgF && dmgS && isDamagable(dmgF, dmgS)) {
          hp->hp -= dmgS->damage;
          if (hp->hp <= 0) {
            emitEvent(this, GameEvent::DEAD, {firstElem});
          }
        }
      }
    }

    bool isDamagable(std::shared_ptr<DamageComponent> e1, std::shared_ptr<DamageComponent> e2)
    {
      return e1->isdmgToMonster != e2->isdmgToMonster;
    }

  };
}