/*
** rtype
** Created on 27/11/18.
*/

#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "Vec2.hpp"
#include "graphic/RessourceManager.hpp"
#include "IScene.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Entity.hpp"
#include "ecs/EcsManager.hpp"
#include "components/WindowComponent.hpp"
#include "components/GameComponent.hpp"

namespace rtype
{
    class Client;

    class SceneManager
    {
    public:
        static constexpr char LOBBY[] = "LOBBY";
        static constexpr char JOIN[] = "JOIN";
        static constexpr char HOME[] = "HOME";
    public:
        explicit SceneManager(Client &client, ecs::EcsManager &ecsManager,
            graphic::RessourceManager &rsManager);
        SceneManager(const SceneManager &other) = delete;
    public:
        void changeScene(const std::string &name);
        void start();
        void startGame(std::shared_ptr<WindowComponent> wdComponent,
            std::shared_ptr<GameComponent> game);
        void setGameOver(bool gameOver) { _game->isOver = gameOver; }
        graphic::RessourceManager &getRessouceManager();
        ecs::Entity &initPlayerController();
        Client &getClient() { return _client; }
        std::shared_ptr<IScene> getScene(const std::string &name) { return _scenes[name]; }
        std::string &getCurrentScene() { return _currentScene; }
    private:
        Client &_client;
        ecs::EcsManager &_ecsManager;
        std::string _currentScene;
        graphic::RessourceManager &_rsManager;
        std::unordered_map<std::string /*name*/, std::shared_ptr<IScene> /*scene*/> _scenes;
        std::shared_ptr<GameComponent> _game;
    };
}