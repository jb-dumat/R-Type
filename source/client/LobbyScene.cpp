/*
** rtype
** Created on 27/11/18.
*/

#include "LobbyScene.hpp"
#include "Client.hpp"
#include "components/ControllerComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"

namespace rtype
{

    LobbyScene::LobbyScene(SceneManager &sceneManager, ecs::EcsManager &ecsManager)
        : _sceneManager(sceneManager), _ecsManager(ecsManager)
    {}

    void LobbyScene::setControllerComponent()
    {
        auto controller = _ecsManager.createEntity().addComponent<ControllerComponent>(
            [&](const graphic::EventResult &eventResult, const ecs::Entity &, ecs::EcsManager &) {
                auto &rs = _sceneManager.getRessouceManager();
                auto buttonTextureSelected = rs.getTexture(TEXTURE::BUTTON_SELECTED);
                auto buttonTextureNotSelected = rs.getTexture(TEXTURE::BUTTON);

                switch (eventResult.type) {
                    case graphic::EventType::ENTER :
                        if (_cursor == _entities.size() - 2) {  // START entity
                            _sceneManager.getClient().interpretCommand(RequestID::TCP_LAUNCH);
                        }
                        if (_cursor == _entities.size() - 1)  // EXIT entity
                            _sceneManager.changeScene(SceneManager::HOME);
                        break;

                    case graphic::EventType::UP :
                        if (_cursor > _entities.size() - 2) {
                            _entities[_cursor].getComponent<SpriteComponent>()->sprite.setTexture(buttonTextureNotSelected);
                            --_cursor;
                            _entities[_cursor].getComponent<SpriteComponent>()->sprite.setTexture(buttonTextureSelected);
                        }
                        break;

                    case graphic::EventType::DOWN :
                        if (_cursor < _entities.size() - 1) {
                            _entities[_cursor].getComponent<SpriteComponent>()->sprite.setTexture(buttonTextureNotSelected);
                            ++_cursor;
                            _entities[_cursor].getComponent<SpriteComponent>()->sprite.setTexture(buttonTextureSelected);
                        }
                        break;

                    default:
                        break;
                }
            });
        _controllerId = controller.id;
    }

    void LobbyScene::initLabels()
    {
        auto &rsManager = _sceneManager.getRessouceManager();

        auto labelRoomId = _ecsManager.createEntity();
        labelRoomId.emplaceComponent<TextComponent>("ROOM ID:", rsManager.getFont(FONT::GALIVER));
        labelRoomId.emplaceComponent<TransformComponent>(10, 10);
        _entities.push_back(labelRoomId);

        auto roomId = _ecsManager.createEntity();
        roomId.emplaceComponent<TextComponent>("loading...", rsManager.getFont(FONT::GALIVER));
        roomId.emplaceComponent<TransformComponent>(175, 10);
        _entities.push_back(roomId);
    }

    void LobbyScene::initSpaceships()
    {
        auto &rsManager = _sceneManager.getRessouceManager();

        auto x = 315;
        auto y = 130;

        for (std::size_t i = 0; i < 4; ++i) {
            if (i == 2) {
                x = 315;
                y = 330;
            }

            auto spaceShipEnt = _ecsManager.createEntity();

            spaceShipEnt.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::SPACESHIP)); // EMPTY doesn't work...
            spaceShipEnt.emplaceComponent<TransformComponent>(x, y);
            _entities.push_back(spaceShipEnt);

            x = 565;
        }
    }

    void LobbyScene::initFrames()
    {
        auto &rsManager = _sceneManager.getRessouceManager();

        auto frameSpaceShipEnt1 = _ecsManager.createEntity();
        frameSpaceShipEnt1.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::FRAME));
        frameSpaceShipEnt1.emplaceComponent<TransformComponent>(300, 100);
        frameSpaceShipEnt1.getComponent<SpriteComponent>()->sprite.setScale(0.22, 0.8);
        _entities.push_back(frameSpaceShipEnt1);

        auto frameSpaceShipEnt2 = _ecsManager.createEntity();
        frameSpaceShipEnt2.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::FRAME));
        frameSpaceShipEnt2.emplaceComponent<TransformComponent>(550, 100);
        frameSpaceShipEnt2.getComponent<SpriteComponent>()->sprite.setScale(0.22, 0.8);
        _entities.push_back(frameSpaceShipEnt2);

        auto frameSpaceShipEnt3 = _ecsManager.createEntity();
        frameSpaceShipEnt3.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::FRAME));
        frameSpaceShipEnt3.emplaceComponent<TransformComponent>(300, 300);
        frameSpaceShipEnt3.getComponent<SpriteComponent>()->sprite.setScale(0.22, 0.8);
        _entities.push_back(frameSpaceShipEnt3);

        auto frameSpaceShipEnt4 = _ecsManager.createEntity();
        frameSpaceShipEnt4.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::FRAME));
        frameSpaceShipEnt4.emplaceComponent<TransformComponent>(550, 300);
        frameSpaceShipEnt4.getComponent<SpriteComponent>()->sprite.setScale(0.22, 0.8);
        _entities.push_back(frameSpaceShipEnt4);
    }

    void LobbyScene::initButtons()
    {
        auto &rsManager = _sceneManager.getRessouceManager();

        auto startButtonEnt = _ecsManager.createEntity();
        startButtonEnt.emplaceComponent<TextComponent>("START", rsManager.getFont(FONT::GALIVER));
        startButtonEnt.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::BUTTON_SELECTED));
        startButtonEnt.getComponent<SpriteComponent>()->sprite.setScale(0.5, 0.5);
        startButtonEnt.emplaceComponent<TransformComponent>(350, 500);
        startButtonEnt.getComponent<TextComponent>()->pos.x = 75;
        startButtonEnt.getComponent<TextComponent>()->pos.y = 20;
        _entities.push_back(startButtonEnt);

        auto exitButtonEnt = _ecsManager.createEntity();
        exitButtonEnt.emplaceComponent<TextComponent>("EXIT", rsManager.getFont(FONT::GALIVER));
        exitButtonEnt.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::BUTTON));
        exitButtonEnt.getComponent<SpriteComponent>()->sprite.setScale(0.5, 0.5);
        exitButtonEnt.emplaceComponent<TransformComponent>(350, 600);
        exitButtonEnt.getComponent<TextComponent>()->pos.x = 90;
        exitButtonEnt.getComponent<TextComponent>()->pos.y = 20;
        _entities.push_back(exitButtonEnt);
    }

    void LobbyScene::initResources()
    {
        /*DO NOT CHANGE THE ORDER*/
        initSpaceships();
        initLabels();
        initFrames();
        initButtons();
    }

    void LobbyScene::displayRoomId(const std::string &roomId)
    {
        _entities[5].getComponent<TextComponent>()->text.setString(roomId);
    }

    void LobbyScene::displayPlayers(std::size_t players)
    {
        std::cout << "Number of players: " << players << std::endl;

        auto &rsManager = _sceneManager.getRessouceManager();

        if (players == 0 || players > 4) {
            std::cerr << "Invalid number of players in the room." << std::endl;
            return;
        }

        auto emptyTexture = rsManager.getTexture(TEXTURE::EMPTY);

        for (std::size_t i = 0; i < 4; ++i) {
            if (i > players - 1) {
                _entities[i].getComponent<SpriteComponent>()->sprite.setTexture(emptyTexture);
                continue;
            }
            auto textureFileName = TEXTURES[TEXTURE::SPACESHIP];

            textureFileName = textureFileName.substr(0, textureFileName.size() - std::string(".png").size());
            textureFileName.pop_back();

            auto newTextureName = textureFileName + std::to_string(i + 1) + ".png";
            auto texture = std::make_shared<graphic::Texture>(newTextureName);

            _entities[i].getComponent<SpriteComponent>()->sprite.setTexture(texture);
        }
    }

    void LobbyScene::load()
    {
        setControllerComponent();

        initResources();

        _cursor = _entities.size() - 2;
        displayPlayers(1);
    }

    void LobbyScene::unload()
    {
        for (auto &it : _entities)
            it.remove();
        _entities.clear();
        ecs::Entity controller(_ecsManager, _controllerId);
        controller.remove();
    }
}