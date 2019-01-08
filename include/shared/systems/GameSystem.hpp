//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Motion System
//

#pragma once

#include "ecs/System.hpp"
#include "RType.hpp"
#include "GameEvent.hpp"
#include "components/PlayerComponent.hpp"
#include "components/StarComponent.hpp"
#include "components/RoomComponent.hpp"
#include "components/MonsterComponent.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Entity.hpp"

namespace rtype {
	class GameSystem : public ecs::System {
  public:
    GameSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager),
    _nbDead(0) {}

  public:

    void update(float) final 
    {
      _ecsManager.forEachEntity<RoomComponent>(
        [&](const ecs::Entity &, auto room){
          _room = room;
        });
      if (!_room)
        return;
      _removeGarbages();
      _handlePlayerDead();
    }

  private:
    void _handlePlayerDead()
    {
      auto events = _ecsManager.fetchEvents(GameEvent::DEAD);
      for (auto &it : events) {
        auto e = it.entities[0];
        if (e.getComponent<PlayerComponent>() != nullptr) {
          e.remove();
          _nbDead += 1;
        }
      }
      if (_nbDead >= (*_room->players).size()) {
        emitEvent(this, GameEvent::GAMEOVER);
        _room->state = States::LOBBY;
      }
    }

    void _removeGarbages()
    {
      std::vector<ecs::Entity> entitiesToRemove;
      _ecsManager.forEachEntity<TransformComponent>(
        [&](const ecs::Entity &e, auto pos) {
          if (e.getComponent<PlayerComponent>() || e.getComponent<StarComponent>())
            return;
          if (e.getComponent<MonsterComponent>() == nullptr &&
            (pos->x < -rtype::WINDOW_WIDTH || pos->x > rtype::WINDOW_WIDTH * 2
              || pos->y < -rtype::WINDOW_HEIGHT || pos->y > rtype::WINDOW_HEIGHT)) {
           entitiesToRemove.push_back(e);
       }
       if (e.getComponent<MonsterComponent>() && pos->x < -rtype::WINDOW_WIDTH)
        emitEvent(this, GameEvent::DEAD, {e});
    });
      for (auto &it : entitiesToRemove)
        it.remove();
    }
  private:
    std::shared_ptr<RoomComponent> _room;
    size_t _nbDead;
  };
}