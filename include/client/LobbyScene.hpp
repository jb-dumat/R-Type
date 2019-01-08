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
    class LobbyScene : public IScene
    {
        private:
            SceneManager &_sceneManager;
            ecs::EcsManager &_ecsManager;
            std::size_t _cursor;
            std::vector<ecs::Entity> _entities;
            size_t _controllerId;
        public:
            explicit LobbyScene(SceneManager &sceneManager, ecs::EcsManager &ecsManager);
            ~LobbyScene() override = default;

            void load() override;
            void unload() override;
            void displayPlayers(std::size_t players);
            void displayRoomId(const std::string &roomId);
        private:
            void initResources();
            void initSpaceships();
            void initLabels();
            void initFrames();
            void initButtons();
            void setControllerComponent();
    };
}
