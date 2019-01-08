/*
** rtype
** Created on 27/11/18.
*/

#pragma once

#include <string>
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
    class JoinScene : public IScene
    {
    private:
        SceneManager &_sceneManager;
        ecs::EcsManager &_ecsManager;
        std::size_t _cursor;
        std::string _roomId;
        std::vector<ecs::Entity> _entities;
        size_t _controllerId;
    public:
        explicit JoinScene(SceneManager &sceneManager, ecs::EcsManager &ecsManager);
        ~JoinScene() override = default;

        void load() override;
        void unload() override;
    };
}
