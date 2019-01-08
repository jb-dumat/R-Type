/*
** rtype
** Created on 27/11/18.
*/

#include "HomeScene.hpp"
#include "Client.hpp"
#include "components/ControllerComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"

namespace rtype
{

    HomeScene::HomeScene(SceneManager &sceneManager, ecs::EcsManager &ecsManager)
    : _sceneManager(sceneManager), _ecsManager(ecsManager), _cursor(0)
    {
        _buttons.push_back({"CREATE", {50, 200}, {80, 20},
            [&]() {
                _sceneManager.getClient().interpretCommand(RequestID::TCP_CREAT);
                sceneManager.changeScene(SceneManager::LOBBY);
            }});
        _buttons.push_back({"JOIN", {50, 350}, {80, 20},
            [&]() {
                sceneManager.changeScene(SceneManager::JOIN);
            }});
        _buttons.push_back({"EXIT", {50, 500}, {80, 20},
            [&]() {
                std::cout << "Exit program" << std::endl;
                exit(0);
            }});
    }

    void HomeScene::load()
    {
        auto controller = _ecsManager.createEntity().addComponent<ControllerComponent>(
            [&](const graphic::EventResult &eventResult, const ecs::Entity &, ecs::EcsManager &) {
                auto &rs = _sceneManager.getRessouceManager();
                auto buttonTextureSelected = rs.getTexture(TEXTURE::BUTTON_SELECTED);
                auto buttonTextureNotSelected = rs.getTexture(TEXTURE::BUTTON);

                switch (eventResult.type) {
                    case graphic::EventType::ENTER :
                    _buttons[_cursor].onSelect();
                    break;

                    case graphic::EventType::UP :
                    if (_cursor > 0) {
                        _entities[_cursor].getComponent<SpriteComponent>()->sprite.setTexture(buttonTextureNotSelected);
                        --_cursor;
                        _entities[_cursor].getComponent<SpriteComponent>()->sprite.setTexture(buttonTextureSelected);
                    }
                    break;

                    case graphic::EventType::DOWN :
                    if (_cursor < _buttons.size() - 1) {
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
        auto &rsManager = _sceneManager.getRessouceManager();
        for (auto &it : _buttons) {
            auto btn = _ecsManager.createGameObject(GO::BUTTON);
            btn.emplaceComponent<TextComponent>(it.text, rsManager.getFont(FONT::GALIVER))
            ->pos = it.textPos;
            btn.getComponent<TransformComponent>()->x = it.pos.x;
            btn.getComponent<TransformComponent>()->y = it.pos.y;
            _entities.push_back(btn);
        }

        auto &rs = _sceneManager.getRessouceManager();
        auto buttonTextureSelected = rs.getTexture(TEXTURE::BUTTON_SELECTED);

        _entities[_cursor].getComponent<SpriteComponent>()->sprite.setTexture(buttonTextureSelected);
    }

    void HomeScene::unload()
    {
        for (auto &it : _entities)
            it.remove();
        _entities.clear();
        ecs::Entity controller(_ecsManager, _controllerId);
        controller.remove();
    }
}