//
// EPITECH PROJECT, 2018
// ElapsedTimeSystem.hpp
// File description:
// ElapsedTime System
//

#pragma once

#include <memory>
#include <iostream>
#include "ecs/System.hpp"
#include "components/ElapsedTimeComponent.hpp"

namespace rtype {
    class ElapsedTimeSystem : public ecs::System {
    public:
        ElapsedTimeSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager)
        {}
    public:
        void update(float dtime) final
        {
          _ecsManager.forEachEntity<ElapsedTimeComponent>(
              [&](const ecs::Entity &, auto etCpn){
                etCpn->eTime += dtime;
              });
        }
    };
}