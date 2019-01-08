/*
** rtype
** Created on 27/11/18.
*/

#include "SceneManager.hpp"
#include "LobbyScene.hpp"
#include "JoinScene.hpp"
#include "HomeScene.hpp"
#include "Client.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/InputSystem.hpp"
#include "components/ControllerComponent.hpp"

namespace rtype
{
	SceneManager::SceneManager(Client &client, ecs::EcsManager &ecsManager,
		graphic::RessourceManager &rsManager) :
	_client(client), _ecsManager(ecsManager),
	_currentScene(HOME), _rsManager(rsManager)
	{
		_scenes[HOME] = std::make_shared<HomeScene>(*this, _ecsManager);
		_scenes[JOIN] = std::make_shared<JoinScene>(*this, _ecsManager);
		_scenes[LOBBY] = std::make_shared<LobbyScene>(*this, _ecsManager);
	}

	void SceneManager::changeScene(const std::string &name)
	{
		_scenes[_currentScene]->unload();
		_currentScene = name;
		_scenes[name]->load();
	}

	void SceneManager::start()
	{
		_scenes[_currentScene]->load();	
		auto sm = _ecsManager.getSystemManager();
		sm->createSystems<RenderSystem, InputSystem>();
		auto gameEntity = _ecsManager.createEntity();
		auto wdComponent = gameEntity.emplaceComponent<WindowComponent>(WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_TITLE);
		_game = gameEntity.emplaceComponent<GameComponent>();
		while (wdComponent->window->isOpen()) {
			_ecsManager.update();
			if (!_game->isOver) {
				startGame(wdComponent, _game);
				changeScene(LOBBY);
			}
		}
	}

	void SceneManager::startGame(std::shared_ptr<WindowComponent> wdComponent,
		std::shared_ptr<GameComponent> game)
	{
		_scenes[_currentScene]->unload();
		auto sm = _ecsManager.getSystemManager();
		auto e = initPlayerController();
		while (wdComponent->window->isOpen() && !game->isOver) {
			_ecsManager.update();
		}
		e.remove();
	}

	ecs::Entity &SceneManager::initPlayerController()
	{
		return _ecsManager.createEntity().addComponent<ControllerComponent>(
			[&](const graphic::EventResult &ev, const ecs::Entity &, ecs::EcsManager &){
				switch (ev.type) {
					case graphic::EventType::UP:
					_client.udpSendMove(0, -1);
					break;
					case graphic::EventType::RIGHT:
					_client.udpSendMove(1, 0);
					break;
					case graphic::EventType::DOWN:
					_client.udpSendMove(0, 1);
					break;
					case graphic::EventType::LEFT:
					_client.udpSendMove(-1, 0);
					break;
					default: break;
				}
			});
	}

	graphic::RessourceManager &SceneManager::getRessouceManager()
	{
		return _rsManager;
	}
}