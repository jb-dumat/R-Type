/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Game
*/

#include <algorithm>
#include <mutex>
#include "Game.hpp"
#include "FrameRate.hpp"
#include "Serializer.hpp"
#include "RType.hpp"
#include "Vec2.hpp"
#include "Utilities.hpp"
#include "systems/ServerComSystem.hpp"
#include "systems/PlayerMovementSystem.hpp"
#include "systems/ElapsedTimeSystem.hpp"
#include "systems/MotionSystem.hpp"
#include "systems/ActionTriggerSystem.hpp"
#include "systems/SpawnMonsterSystem.hpp"
#include "systems/StarfieldSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/LifeSystem.hpp"
#include "systems/MonsterSystem.hpp"
#include "systems/GameSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/RoomComponent.hpp"
#include "components/MotionComponent.hpp"
#include "components/ActionSequenceComponent.hpp"
#include "components/ElapsedTimeComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/BulletComponent.hpp"
#include "components/StarComponent.hpp"
#include "components/BoundingBoxComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/DamageComponent.hpp"
#include "components/PlayerComponent.hpp"

static std::mutex mutex;

rtype::Game::Game(std::shared_ptr<std::list<std::shared_ptr<rtype::Player>>> &clients,
	std::shared_ptr<std::vector<std::shared_ptr<MonsterComponent>>> monsters,
	size_t uid)
:	_clients(clients), _monsters(monsters), _uid(uid), _status(States::LOBBY), _host(nullptr), _MAX_SLOT(DEFAULT_SLOT)
{
	for (auto &pair : rtype::ACTIONS)
		_actions.emplace(pair.first, rtype::parseActions(pair.second));
}

bool rtype::Game::contains(std::shared_ptr<rtype::Player> player)
{
	return (std::find(_clients->begin(), _clients->end(), player) == _clients->end()) ? false : true;
}

std::shared_ptr<rtype::Player> rtype::Game::remove(std::shared_ptr<rtype::Player> player)
{
	_clients->remove(player);
	if (_host && _host == player.get() && _clients->size() > 0)
		setHost(_clients->front().get());
	else
		setHost(nullptr);
	return player;
}

std::shared_ptr<rtype::Player> rtype::Game::add(std::shared_ptr<rtype::Player> player)
{
	_clients->push_back(player);
	return player;
}

void rtype::Game::display()
{
	std::unique_lock<std::mutex> lock(mutex); // DEBUG
	std::cout << "------------ GAME INFOS --------------" << std::endl;
	std::cout << "Game " << _uid << std::endl;
	std::cout << "Game capacity: " << _clients->size() << "/" << _MAX_SLOT << " players." << std::endl;
	std::cout << "Host: " << _host << std::endl;
	std::cout << "Players: ";
	for (auto &it : *_clients) {
		std::cout << "[" << it->uid << "] ";
	}
	std::cout << "Game status (LOBBY/GAME): " << _status << std::endl;
	std::cout << std::endl;
	std::cout << "---------------------------------------" << std::endl;
}

void rtype::Game::initStars()
{
	for (size_t i = 0; i < 200; i++) {
		auto x = hutils::randInt(0, rtype::WINDOW_WIDTH);
		auto y = hutils::randInt(0, rtype::WINDOW_HEIGHT - 10);
		auto speed = hutils::randInt(10, 30);
		_ecsManager.createEntity()
		.addComponent<StarComponent>()
		.addComponent<SpriteComponent>(speed > 20 ? TEXTURE::STAR2 : TEXTURE::STAR)
		.addComponent<TransformComponent>(x, y)
		.addComponent<MotionComponent>(-1, 0, speed);
	}
}

std::shared_ptr<rtype::RoomComponent> rtype::Game::initRoom()
{
	auto room = _ecsManager.createEntity()
	.emplaceComponent<rtype::RoomComponent>(_clients, _monsters, _status);
	std::ifstream infile(rtype::GAME_CONFIG_FILE);
	std::string line;
	std::getline(infile, line);
	std::istringstream iss(line);
	iss >> room->minMonster >> room->maxMonster >> room->spawnRate;
	room->windowWidth = rtype::WINDOW_WIDTH;
	room->windowHeight = rtype::WINDOW_HEIGHT;
	return room;
}

void rtype::Game::addSpaceShip(std::shared_ptr<rtype::Player> player, size_t idx)
{
	auto y = hutils::randInt(0, rtype::WINDOW_HEIGHT - 100);
	auto ett = _ecsManager.createEntity()
	.addComponent<TransformComponent>(0, y)
	.addComponent<BoundingBoxComponent>(hutils::Vec2<float>(0, y),
		hutils::Vec2<float>(85, 63))
	.addComponent<SpriteComponent>(rtype::TEXTURE::SPACESHIP + idx)
	.addComponent<MotionComponent>(0, 0, 200)
	.addComponent<ElapsedTimeComponent>(0)
	.addComponent<HealthComponent>(1)
	.addComponent<DamageComponent>(1, true)
	.addComponent<BulletComponent>(rtype::TEXTURE::BULLET, 1, hutils::Vec2<float>(97, 48))
	.addComponent<ActionSequenceComponent>(_actions[rtype::ACTION::PLAYER_ACTION])
	.addComponent<PlayerComponent>();
	player->eid = ett.id;
}

void rtype::Game::gameLoop()
{
	std::cout << "------{ GAME " << _uid << " LAUNCHED }------" << std::endl;
	auto room = initRoom();
	initStars();
	while (_clients->size() > 0) {
		room->state = _status;
		if (_status == rtype::States::GAME)
			startGame(room);
	}
	std::cout << "------{ GAME " << _uid << "FINISHED }------" << std::endl;
}

void rtype::Game::startGame(std::shared_ptr<rtype::RoomComponent> room)
{
	FrameRate updateFrame(FRAME_RATE);
	auto sm = _ecsManager.getSystemManager();
	sm->createSystems<ServerComSystem, PlayerMovementSystem, ElapsedTimeSystem, SpawnMonsterSystem,
	MotionSystem, ActionTriggerSystem, StarfieldSystem, CollisionSystem,
	LifeSystem, MonsterSystem, GameSystem>();
	size_t idx = 0;
	for (auto &it : *_clients) {
		addSpaceShip(it, idx);
		idx += 1;
	}
	while (room->state == rtype::States::GAME) {
		if (updateFrame.canUpdateFrame()) {
			_ecsManager.update(updateFrame.elapsedSeconds());
			updateFrame.reset();
		}
	}
	notifyLobbyPlayers(_uid, _clients->size());
	_status = room->state;
}

void rtype::Game::notifyLobbyPlayers(size_t gid, size_t nplayers)
{
	auto p = Serializer::makeRequest(
		Serializer::makePayload(RequestID::UDP_LOBBY_DATA, gid, nplayers));
	for (auto &it : *_clients) {
		it->usocket->send(p.first, p.second);
	}
}