//
// EPITECH PROJECT, 2018
// InputSystem.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <memory>
#include <iostream>
#include "ecs/System.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/WindowComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "graphic/IEvent.hpp"

namespace rtype {
    class InputSystem : public ecs::System {
    public:
        InputSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager)
        {}
    public:
        void update(float) final
        {
            if (!_wdCpn)
                _ecsManager.forEachEntity<WindowComponent>(
                    [&](const ecs::Entity &, auto wd){
                        _wdCpn = wd;
                    });
            if (_wdCpn)
                notifyControllers();
        }
    private:
        void notifyControllers()
        {
            auto event = _wdCpn->window->getEvent();
            if (event.type == graphic::EventType::NONE)
                return;
            _ecsManager.forEachEntity<ControllerComponent>([&, event]
                (const ecs::Entity &e, auto controller) {
                    if (controller->onInput)
                      controller->onInput(event, e, _ecsManager);
              });
        }
    private:
        std::shared_ptr<WindowComponent> _wdCpn;
    };
}