/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Server
*/

#include <iostream>

#include "Server.hpp"
#include "RType.hpp"
#include "GameEvent.hpp"
#include "systems/ServerComSystem.hpp"
#include "components/MotionComponent.hpp"

rtype::Server::Server(net::NetworkService &netService)
: _players(), _monsters(std::make_shared<std::vector<std::shared_ptr<rtype::MonsterComponent>>>()),
_netService(netService), _cmdManager(std::make_unique<rtype::CommandManager>()),
_pool(std::make_unique<async::ThreadPool>(std::thread::hardware_concurrency() * 2)),
_tsocket(netService), _usocket(netService, SERVER_IP), _serverWrapper(*this)
{
	_cmdManager->registerCommand("load", [&](const std::vector<std::string> &params) {
		int i = 0;
		for (auto &it : params) {
			if (i != 0)
				loadMonster(it);
			i++;
		}
	});
	if (_tsocket.bind(SERVER_PORT))
		_tsocket.accept([&](net::ISocket *socket, void *) { handlePlayerConnection(socket); });

	if (_usocket.bind(SERVER_PORT))
		_usocket.receive([&](const char *data, size_t size, void *usocket) {
			handleUDPPayloadReception(static_cast<net::UDPSocket*>(usocket), data, size);
		}, &_usocket);
	_pool->post(std::bind(&net::NetworkService::run, std::ref(netService)));
	_pool->post(std::bind(&rtype::CommandManager::readStandardInput, std::ref(*_cmdManager)));
	loadMonster("./monsters/SimpleMonster.so");
	loadMonster("./monsters/BasicMonster.so");
	_serverLoop();
}

rtype::Server::~Server()
{
	for (auto &it : _players)
		delete it.second->usocket;
}

void rtype::Server::loadMonster(const std::string &monsterFile)
{
	auto monster = _dlloader.getInstance(monsterFile, rtype::GET_MONSTER_FUNC);
	if (monster == nullptr) {
		std::cerr << "Failed to load monster from " << monsterFile << std::endl;
		return;
	}
	_monsters->emplace_back(monster);
}

void rtype::Server::handlePlayerConnection(net::ISocket *socket)
{
	_players[gen.uid] = std::make_shared<Player>(gen.uid);
	auto playerSocket = static_cast<net::TCPSocket*>(socket);
	playerSocket->onDisconnect([this, playerSocket](net::ISocket *socket, void *) { handlePlayerDisconnection(socket); });
	playerSocket->receive([&](const char *data, size_t size, void *isocket) { handleTCPPayloadReception(static_cast<net::TCPSocket*>(isocket), data, size); }, socket);
	_players[gen.uid++]->tsocket = std::shared_ptr<net::TCPSocket>(playerSocket);
}

std::shared_ptr<rtype::Player> rtype::Server::getPlayerbySocket(net::ISocket *socket)
{
	std::cout << "Searching in sockets:" << std::endl;
	for (auto &it : _players) {
		std::cout << socket << " <--> " << it.second->tsocket.get() << std::endl;
		if (it.second->tsocket.get() == socket || it.second->usocket == socket) {
			it.second->display();
			return it.second;
		}
	}
	std::cout << "Not Found..." << std::endl;
	return nullptr;
}

void rtype::Server::handleTCPPayloadReception(net::TCPSocket *socket, const char *data, size_t size)
{
	std::cout << "handle tcp payload reception." << std::endl;
	std::vector<char> vstr;
	for (size_t i = 0; i < size; i++)
		vstr.push_back(data[i]);

	auto player = getPlayerbySocket(socket);
	if (player != nullptr)
		_serverWrapper.handleRequest(player, vstr);
}

void rtype::Server::handleUDPPayloadReception(net::UDPSocket *socket, const char *data, size_t size)
{
	std::cout << "handle udp payload reception." << std::endl;
	std::vector<char> vstr;
	for (size_t i = 0; i < size; i++)
		vstr.push_back(data[i]);
	_serverWrapper.handleRequest(socket, vstr);
}

std::shared_ptr<rtype::Player> rtype::Server::getPlayerbyUid(size_t uid)
{
	return _players[uid];
}

void rtype::Server::handlePlayerDisconnection(net::ISocket *socket)
{
	auto player = getPlayerbySocket(socket);
	if (player == nullptr)
		return;
	std::cout << "[ Player " << player->uid << " disconnected ]" << std::endl;
	if (player->status != States::IDDLE) {
		auto guid = player->guid;
		if (_games.find(guid) != _games.end())
			_games[guid]->remove(player)->setIddle();
	}
	delete _players[player->uid]->usocket;
	_players.erase(player->uid);
}

void rtype::Server::_serverLoop()
{
	while(1);
}

void rtype::Server::_tcpQuit(const std::shared_ptr<rtype::Player> player)
{
	handlePlayerDisconnection(player->tsocket.get());
}

void rtype::Server::_tcpSendJoinResp(net::ISocket *socket, char resp)
{
	auto p = Serializer::makeRequest(Serializer::makePayload(RequestID::TCP_JOIN_RESP, resp));
	socket->send(p.first, p.second);
}

void rtype::Server::_tcpSendLaunch(size_t guid)
{
	auto &game = _games[guid];

	for (auto &it : game->getList()) {
		auto p = Serializer::makeRequest(Serializer::makePayload(RequestID::TCP_LAUNCH));
		it->tsocket->send(p.first, p.second);
	}
}

void rtype::Server::_tcpJoinGame(std::shared_ptr<rtype::Player> player, size_t uidGame)
{
	if (_games.find(uidGame) == _games.end()) {
		std::cerr << "{ JOIN: game " << uidGame << " not found. }" << std::endl;
		return;
	}
	auto &game = _games[uidGame];
	if (player->status == States::IDDLE) {
		if (!game->isFull()) {
			game->add(player)->assign(uidGame, game->getStatus()).setHost(false);
			if (game->hasNoHost())
				game->setHost(player.get())->setHost(true);
			_tcpSendJoinResp(player->tsocket.get(), 1);
			game->notifyLobbyPlayers(uidGame, game->getSlotCapacity() - game->getNbFreeSlot());
			std::cout << "[ Player " << player->uid << " joined the game " << uidGame << ". ]" << std::endl;
			return;
		}
	}
	_tcpSendJoinResp(player->tsocket.get(), 0);
	std::cerr << "{ JOIN: game " << uidGame << " failed. }" << std::endl;
}

void rtype::Server::_tcpLeaveGame(std::shared_ptr<rtype::Player> player)
{
	auto guid = player->guid;
	if (player->status != States::IDDLE && _games.find(guid) != _games.end()) {
		auto &game = _games[guid];
		game->remove(player)->setIddle();
		std::cout << "[ Player " << player->uid << " has left the game. ]" << std::endl;
		game->notifyLobbyPlayers(guid, game->getSlotCapacity() - game->getNbFreeSlot());
		return;
	}
	std::cerr << "{ LEAVE: game " << guid << " failed. }" << std::endl;
}

void rtype::Server::_tcpCreateGame(std::shared_ptr<rtype::Player> player)
{
	if (player->status == States::IDDLE) {
		auto players = std::make_shared<std::list<std::shared_ptr<Player>>>();
		auto uid = gen.uid++;
		_games[uid] = std::make_unique<Game>(players, _monsters, uid);
		auto &ref = _games[uid];
		ref->add(player)->assign(ref->getGameID(), ref->getStatus()).setHost(true);
		ref->setHost(player.get());
		_pool->post(std::bind(&Game::gameLoop, std::ref(*ref)));
		// _tcpSendJoinResp(player->tsocket.get(), 1);
		ref->notifyLobbyPlayers(uid, ref->getSlotCapacity() - ref->getNbFreeSlot());
		std::cout << "[ Game " << ref->getGameID() << " created ]" << std::endl;
		return;
	}
	_tcpSendJoinResp(player->tsocket.get(), 0);
	std::cerr << "{ CREATE: game failed. }" << std::endl;
}

void rtype::Server::_tcpLaunchGame(std::shared_ptr<rtype::Player> player)
{
	auto guid = player->guid;
	if (player->isHost && _games.find(guid) != _games.end()) {
		_games[guid]->setStatus(States::GAME);
		_tcpSendLaunch(guid);
		std::cout << "[ Game " << guid << " has been launched ]" << std::endl;
		return;
	}
	std::cerr << "{ LAUNCH: game " << guid << " failed." << " player is host: " << std::boolalpha << player->isHost << " }" << std::endl;
}

void rtype::Server::_tcpAddSlot(std::shared_ptr<rtype::Player> player, size_t nb)
{
	auto guid = player->guid;
	if (player->isHost && _games.find(guid) != _games.end()) {
		_games[guid]->setNbSlot(nb);
		std::cout << "[ added " << nb << " new slot(s)." << std::endl;
		return;
	}
	std::cerr << "{ ADD SLOT: game " << guid << " failed."  << " player is host: " << std::boolalpha << player->isHost << " }" << std::endl;
}

void rtype::Server::_tcpDelSlot(std::shared_ptr<rtype::Player> player, size_t nb)
{
	auto guid = player->guid;
	if (player->isHost && _games.find(guid) != _games.end()) {
		_games[guid]->setNbSlot(-nb);
		std::cout << "[ removed " << nb << " slot(s)." << std::endl;
		return;
	}
	std::cerr << "{ DEL SLOT: game " << guid << " failed."  << " player is host: " << std::boolalpha << player->isHost << " }" << std::endl;
}

void rtype::Server::_tcpUDPSetup(std::shared_ptr<rtype::Player> client, const std::vector<char> &ip, int port)
{
	std::string sip;
	for (auto &it : ip)
		sip.push_back(it);
	std::cout << "Connect udp socket for [" << sip << ":" << port << "]." << std::endl;
	auto uid = client->uid;
	auto usocket = new net::UDPSocket(_netService);
	_players[uid]->usocket = usocket;
	auto *socket = _players[uid]->usocket;
	if (!socket->connect(sip, port)) {
		std::cerr << "[ Server has failed to connect to client " << client->uid << " UDP Socket (Connect) ]" << std::endl;
		return;
	}
	_tcpAssignUid(_players[uid]->tsocket.get(), uid);
	std::cout << "[ Server has connected to client " << client->uid << " UDP Socket " << client->usocket << "]" << std::endl;
}

void rtype::Server::_tcpRequireUid(std::shared_ptr<rtype::Player> player)
{
	_tcpAssignUid(player->tsocket.get(), player->uid);
}

void rtype::Server::_tcpAssignUid(net::ISocket *socket, size_t uid)
{
	auto p = Serializer::makeRequest(Serializer::makePayload(RequestID::TCP_ASSIGN_UID, uid));
	socket->send(p.first, p.second);
}

void rtype::Server::_udpMove(std::shared_ptr<rtype::Player> player, float x, float y)
{
	if (_games.find(player->guid) == _games.end())
		return;
	auto &ecsManager = _games[player->guid]->getEcsManager();
	ecs::Entity e(ecsManager, player->eid);
	if (e.getComponent<MotionComponent>() == nullptr) {
		std::cerr << "udpMove: entity doesn't exist." << std::endl;
		return;
	}
	e.getComponent<MotionComponent>()->x = x;
	e.getComponent<MotionComponent>()->y = y;
	ecsManager.emitEvent<rtype::ServerComSystem>(rtype::GameEvent::PLAYER_MOVE, {e});
}