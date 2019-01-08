/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Client
*/

#include <functional>
#include <utility>
#include "Client.hpp"
#include "LobbyScene.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"

rtype::Client::Client(ecs::EcsManager &ecsManager, net::NetworkService &netservice)
:	_tsocket(netservice), _usocket(netservice, net::getMyIP()),
_ecsManager(ecsManager), _sceneManager(*this, ecsManager, _rsManager),
_pool(std::thread::hardware_concurrency() * 2), _uid(-1), _clientWrapper(*this)
{

}

rtype::Client::~Client()
{

}

void rtype::Client::handleTCPPayloadReception(net::TCPSocket *, const char *data, size_t size)
{
	// std::cout << "handle tcp payload reception." << std::endl;
	std::vector<char> vstr;
	for (size_t i = 0; i < size; i++)
		vstr.push_back(data[i]);
	_clientWrapper.handleRequest(vstr);
}

void rtype::Client::handleUDPPayloadReception(net::UDPSocket *socket, const char *data, size_t size)
{
	// std::cout << "handle udp payload reception." << std::endl;
	std::vector<char> vstr;
	for (size_t i = 0; i < size; i++)
		vstr.push_back(data[i]);
	_clientWrapper.handleRequest(socket, vstr);
}

void rtype::Client::interpretCommand(rtype::RequestID id, size_t arg)
{
	std::cout << "Sending payload..." << std::endl;
	std::pair<const char*, size_t> data;
	switch (id) {
		case RequestID::TCP_CREAT:
		data = Serializer::makeRequest(rtype::Serializer::makePayload(id));
		break;
		case RequestID::TCP_JOIN:
		data = Serializer::makeRequest(rtype::Serializer::makePayload(id, arg));
		break;
		case RequestID::TCP_LEAVE:
		data = Serializer::makeRequest(rtype::Serializer::makePayload(id));
		break;
		case RequestID::TCP_LAUNCH:
		data = Serializer::makeRequest(rtype::Serializer::makePayload(id));
		break;
		case RequestID::TCP_ADD_SLOT:
		data = Serializer::makeRequest(rtype::Serializer::makePayload(id, arg));
		break;
		case RequestID::TCP_DEL_SLOT:
		data = Serializer::makeRequest(rtype::Serializer::makePayload(id, arg));
		break;
		case RequestID::TCP_QUIT:
		data = Serializer::makeRequest(rtype::Serializer::makePayload(id));
		break;
		default: std::cout << "No id found for " << (int)id << std::endl; break;
	}
	_tsocket.send(data.first, data.second);
}

void rtype::Client::loop()
{
	int id = 0;
	size_t arg = 0;
	while (true) {
		try {
			std::cout << "Enter command: ";
			std::cin >> id >> arg;
			std::cout << std::endl << "command: " << id << " - " << arg << std::endl;
			interpretCommand((RequestID)id, arg);
			if (id == (int)RequestID::TCP_QUIT) {
				_pool.stop();
				break;
			}
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

namespace rtype {
	bool IS_DEBUG = false;

	int Client::launch(net::NetworkService &netservice)
	{
		_pool.post(std::bind(&net::NetworkService::run, std::ref(netservice)));
		if (!_tsocket.connect(SERVER_IP, SERVER_PORT)) {
			std::cerr << "Failed to connect server tcp socket" << std::endl;
			return FAIL_CODE;
		}
		_tsocket.receive([&](const char *data, size_t size, void *isocket) {
			handleTCPPayloadReception(static_cast<net::TCPSocket*>(isocket), data, size);
		}, &_tsocket);

		if (!_usocket.connect(SERVER_IP, SERVER_PORT)) {
			std::cerr << "Failed to connect server udp socket." << std::endl;
			return FAIL_CODE;
		}
		if (_usocket.bind(0)) {
			_usocket.receive([&](const char *data, size_t size, void *isocket) {
				handleUDPPayloadReception(static_cast<net::UDPSocket*>(isocket), data, size);
			}, &_usocket);
		}
		std::cout << "usocket binded on " << _usocket.getPort() << std::endl;
		_tcpSendUdpSetup();
		if (IS_DEBUG) {
			loop();
			return SUCCESS_CODE;
		}
		initRessources();
		initGameObjects();
		_sceneManager.start();
		return SUCCESS_CODE;
	}

	void Client::initRessources()
	{
		for (auto &pair : TEXTURES)
			_rsManager.createTexture(pair.first, pair.second);
		for (auto &pair : FONTS)
			_rsManager.createFont(pair.first, pair.second);
	}

	void Client::initGameObjects()
	{
		auto &btnModel = _ecsManager.registerGameObject(GO::BUTTON)
		.addComponent<SpriteComponent>(_rsManager.getTexture(TEXTURE::BUTTON))
		.addComponent<TransformComponent>(0, 0);
		btnModel.getComponent<SpriteComponent>()->sprite.setScale(0.5, 0.5);
	}

	void Client::_udpReceiveID(size_t id)
	{
		std::cout << id << std::endl;
		_eid = id;
	}

	void Client::_udpReceiveEntity(size_t eId, size_t textureId, float x, float y)
	{
		auto texture = _rsManager.getTexture(textureId);
		if (_entitiesMap.find(eId) == _entitiesMap.end()) {
			auto e = _ecsManager.createEntity().addComponent<TransformComponent>(x, y);
			if (texture)
				e.addComponent<SpriteComponent>(texture);
			_entitiesMap.emplace(eId, e.id);
			return;
		}
		ecs::Entity ett(_ecsManager, _entitiesMap[eId]);
		if (texture)
			ett.getComponent<SpriteComponent>()->sprite.setTexture(texture);
		ett.getComponent<TransformComponent>()->x = x;
		ett.getComponent<TransformComponent>()->y = y;
	}
}

void rtype::Client::_udpReceiveEntityRemove(size_t eid)
{
	ecs::Entity e(_ecsManager, eid);
	e.remove();
	std::cout << "[ Entity " << eid << " removed from the game. ]" << std::endl;
}

void rtype::Client::_askForNewUid()
{
	while (_uid == static_cast<size_t>(-1)) {
		std::cout << "Awaiting for a new UID from server" << std::endl;
		_tcpSendRequireUid();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void rtype::Client::_tcpSendUdpSetup()
{
	auto sip = net::getMyIP();
	std::vector<char> vip;
	std::cout << "My ip: ";
	for (size_t i = 0; i != sip.size(); i++) {
		vip.push_back(sip[i]);
		std::cout << vip.back();
	}
	std::cout << std::endl;
	auto p = Serializer::makeRequest(rtype::Serializer::makePayload(RequestID::TCP_UDP_SETUP,
		vip, _usocket.getPort()));
	_tsocket.send(p.first, p.second);
	_askForNewUid();
}

void rtype::Client::udpSendMove(float x, float y)
{
	auto p = rtype::Serializer::makeRequest(rtype::Serializer::makePayload(RequestID::UDP_MOVE, _uid, x, y));
	_usocket.send(p.first, p.second);
}

void rtype::Client::_udpReceiveSound(size_t sid)
{
	std::cout << "[ Received sound with id " << sid << " ]" << std::endl;
}

void rtype::Client::_udpReceiveGameOver()
{
	std::cout << "[ Received Game Over ]" << std::endl;
	for (auto &pair : _entitiesMap) {
		ecs::Entity ett(_ecsManager, pair.second);
		ett.remove();
	}
	_sceneManager.setGameOver(true);
	_entitiesMap.clear();
}

void rtype::Client::_udpReceiveLobbyData(size_t gid, size_t nplayers)
{
	std::cout << "[ Received lobby data, gid: " << gid << " | nb players: " << nplayers << " ]" << std::endl;
	auto lobby = static_cast<rtype::LobbyScene *>(_sceneManager.getScene(SceneManager::LOBBY).get());
	lobby->displayPlayers(nplayers);
	lobby->displayRoomId(std::to_string(gid));
}

void rtype::Client::_tcpAssignUid(size_t uid)
{
	_uid = uid;
	std::cout << "[ New uid: " << uid << " assigned by the server. ]" << std::endl;
}

void rtype::Client::_tcpSendRequireUid()
{
	auto p = Serializer::makeRequest(rtype::Serializer::makePayload(RequestID::TCP_REQUIRE_UID));
	_usocket.send(p.first, p.second);
}

void rtype::Client::_tcpReceiveJoinResp(bool resp)
{
	if (resp) {
		_sceneManager.changeScene(SceneManager::LOBBY);
		std::cout << "[ Successfully joined room. ]" << std::endl;
		return;
	}
	std::cout << "[ Failed to join room. ]" << std::endl;
}

void rtype::Client::_tcpReceiveLaunch()
{
	_sceneManager.setGameOver(false);
}