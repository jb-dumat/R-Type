/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Game
*/

#pragma once

#include <list>
#include <memory>
#include <vector>
#include "Player.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Entity.hpp"
#include "Action.hpp"
#include "components/MonsterComponent.hpp"
#include "components/RoomComponent.hpp"
#include "Serializer.hpp"

namespace rtype {

	static constexpr char GAME_CONFIG_FILE[] = "./assets/game.config";

	enum ACTION {
		PLAYER_ACTION = 0
	};

	static std::unordered_map<int, std::string> ACTIONS = {
		{ACTION::PLAYER_ACTION, "./assets/actions/playerShoot.action"}
	};

	class Game {
	public:
		Game(std::shared_ptr<std::list<std::shared_ptr<Player>>> &clientList,
			std::shared_ptr<std::vector<std::shared_ptr<MonsterComponent>>> monsters,
			size_t uid);
		~Game() = default;

	public:
		inline friend bool operator==(const Game& le, const Game& re) { return le.getGameID() == re.getGameID(); }
		friend std::hash<Game>;

	public:
		void gameLoop();
		void startGame(std::shared_ptr<rtype::RoomComponent>);
		void initStars();
		std::shared_ptr<RoomComponent> initRoom();
		void addSpaceShip(std::shared_ptr<Player> player, size_t idx);
	public:
		inline bool isFull() const { return _clients->size() == _MAX_SLOT; }
		inline bool isEmpty() const { return _clients->empty(); }
		bool contains(std::shared_ptr<Player> client);
		inline size_t setNbSlot(size_t nb) { _MAX_SLOT += nb; return _MAX_SLOT; }
		inline size_t getSlotCapacity() const { return _MAX_SLOT; }
		inline size_t getNbFreeSlot() const { return _MAX_SLOT - _clients->size(); }
		inline States getStatus() const { return _status; }
		inline Player *setHost(Player *player) { _host = player; return player; }
		inline bool hasNoHost() const { return _host == nullptr; }
		inline States setStatus(States status) { _status = status; return _status; }
		inline ecs::EcsManager &getEcsManager() { return _ecsManager; }
		std::shared_ptr<Player> add(std::shared_ptr<Player> player);
		std::shared_ptr<Player> remove(std::shared_ptr<Player> player);
		void display();
		inline std::list<std::shared_ptr<Player>> &getList() const {
			return *_clients;
		}

	public:
		void notifyLobbyPlayers(size_t gid, size_t nplayers);
		inline size_t getGameID() const { return _uid; }

	private:
		std::shared_ptr<std::list<std::shared_ptr<Player>>> _clients;
		std::shared_ptr<std::vector<std::shared_ptr<MonsterComponent>>> _monsters;
		size_t _uid;
		States _status;
		Player *_host;
		ecs::EcsManager _ecsManager;
		size_t _MAX_SLOT;
		std::unordered_map<int, std::vector<Action>> _actions;
	};
	static const size_t DEFAULT_SLOT = 4;
}

namespace std {
	template<> struct hash<rtype::Game> {
	size_t operator()(rtype::Game const& e) const {
		return std::hash<size_t>{}(e.getGameID());
	}
};
}
