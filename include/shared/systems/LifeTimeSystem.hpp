//
// EPITECH PROJECT, 2018
// ElapsedTimeSystem.hpp
// File description:
// LifeTimeSystem System
//

#pragma once

#include <memory>
#include <iostream>
#include "ecs/System.hpp"
#include "components/LifeTimeComponent.hpp"
#include "components/ElapsedTimeComponent.hpp"

namespace rtype {
    class LifeTimeSystem : public ecs::System {
    public:
        LifeTimeSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager)
        {}
    public:
        void update(float dtime) final
        {
          _ecsManager.forEachEntity<ElapsedTimeComponent, LifeTimeComponent>(
              [&](const ecs::Entity &e, auto eTime, auto lTime){
                if (eTime->eTime > lTime->lTime)
                    e.remove();
              });
        }
    };
}