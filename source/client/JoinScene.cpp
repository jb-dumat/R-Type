/*
** rtype
** Created on 27/11/18.
*/

#include "JoinScene.hpp"
#include "Client.hpp"
#include "components/ControllerComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"

namespace rtype
{

    JoinScene::JoinScene(SceneManager &sceneManager, ecs::EcsManager &ecsManager)
    : _sceneManager(sceneManager), _ecsManager(ecsManager), _cursor(1)
    {

    }

    void JoinScene::load()
    {
        auto controller = _ecsManager.createEntity().addComponent<ControllerComponent>(
            [&](const graphic::EventResult &eventResult, const ecs::Entity &, ecs::EcsManager &) {
                auto &rs = _sceneManager.getRessouceManager();
                auto buttonTextureSelected = rs.getTexture(TEXTURE::BUTTON_SELECTED);
                auto buttonTextureNotSelected = rs.getTexture(TEXTURE::BUTTON);

                switch (eventResult.type) {
                    case graphic::EventType::ENTER :
                    if (_cursor == _entities.size() - 2) {
                        std::cout << "Joining room " << std::stoi(_roomId) << std::endl;
                        _sceneManager.getClient().interpretCommand(RequestID::TCP_JOIN, std::stoi(_roomId));
                    }
                    if (_cursor == _entities.size() - 1)
                        _sceneManager.changeScene(SceneManager::HOME);
                    break;

                    case graphic::EventType::UP :
                    if (_cursor > 1) {
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

                    case graphic::EventType::BACKSPACE :
                    if (_cursor == 1) {
                        if (!_roomId.empty()) {
                            _roomId.pop_back();
                            if (_roomId.empty())
                                _entities[_cursor].getComponent<TextComponent>()->text.setString("_______");
                            else
                                _entities[_cursor].getComponent<TextComponent>()->text.setString(_roomId);
                        }
                    }
                    break;

                    case graphic::EventType::TEXT :
                    if (_cursor == 1 && _roomId.size() < 7) {
                        if (std::isdigit(eventResult.key)) {
                            _roomId.append(1, eventResult.key);
                            _entities[_cursor].getComponent<TextComponent>()->text.setString(_roomId);
                        }
                    }
                    break;

                    default:
                    break;
                }
            });
        _controllerId = controller.id;
        auto &rsManager = _sceneManager.getRessouceManager();

        auto labelEnt = _ecsManager.createEntity();
        labelEnt.emplaceComponent<TextComponent>("ROOM ID:", rsManager.getFont(FONT::GALIVER));
        labelEnt.emplaceComponent<TransformComponent>(50, 200);
        _entities.push_back(labelEnt);

        auto roomIdEnt = _ecsManager.createEntity();
        roomIdEnt.emplaceComponent<TextComponent>("_______", rsManager.getFont(FONT::GALIVER));
        roomIdEnt.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::BUTTON_SELECTED));
        roomIdEnt.getComponent<SpriteComponent>()->sprite.setScale(0.5, 0.5);
        roomIdEnt.emplaceComponent<TransformComponent>(325, 200);
        roomIdEnt.getComponent<TextComponent>()->pos.x = 75;
        roomIdEnt.getComponent<TextComponent>()->pos.y = 20;

        _entities.push_back(roomIdEnt);

        auto joinButtonEnt = _ecsManager.createEntity();
        joinButtonEnt.emplaceComponent<TextComponent>("JOIN", rsManager.getFont(FONT::GALIVER));
        joinButtonEnt.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::BUTTON));
        joinButtonEnt.emplaceComponent<TransformComponent>(200, 400);
        joinButtonEnt.getComponent<TextComponent>()->pos.x = 210;
        joinButtonEnt.getComponent<TextComponent>()->pos.y = 50;
        _entities.push_back(joinButtonEnt);

        auto exitButtonEnt = _ecsManager.createEntity();
        exitButtonEnt.emplaceComponent<TextComponent>("BACK", rsManager.getFont(FONT::GALIVER));
        exitButtonEnt.emplaceComponent<SpriteComponent>(rsManager.getTexture(TEXTURE::BUTTON));
        exitButtonEnt.getComponent<SpriteComponent>()->sprite.setScale(0.5, 0.5);
        exitButtonEnt.emplaceComponent<TransformComponent>(325, 600);
        exitButtonEnt.getComponent<TextComponent>()->pos.x = 85;
        exitButtonEnt.getComponent<TextComponent>()->pos.y = 20;
        _entities.push_back(exitButtonEnt);
    }

    void JoinScene::unload()
    {
        for (auto &it : _entities) {
            it.remove();
        }
        _entities.clear();
        ecs::Entity controller(_ecsManager, _controllerId);
        controller.remove();
    }
}