/*
** rtype
** Created on 27/11/18.
*/

#pragma once

#include "IScene.hpp"
#include "SceneManager.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Component.hpp"
#include "ecs/EntityManager.hpp"
#include "ecs/Entity.hpp"
#include "ecs/EcsManager.hpp"
#include "ecs/System.hpp"

namespace rtype
{
    class HomeScene : public IScene
    {
    private:
        SceneManager &_sceneManager;
        ecs::EcsManager &_ecsManager;
        std::vector<ButtonInfo> _buttons;
        std::size_t _cursor;
        std::vector<ecs::Entity> _entities;
        size_t _controllerId;
    public:
        explicit HomeScene(SceneManager &sceneManager, ecs::EcsManager &ecsManager);
        ~HomeScene() override = default;

        void load() override;
        void unload() override;
    };
}
