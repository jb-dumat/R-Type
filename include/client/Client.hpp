/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Client
*/

#pragma once
#include <unordered_map>
#include "SceneManager.hpp"
#include "net/Net.hpp"
#include "net/UDPSocket.hpp"
#include "net/TCPSocket.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Entity.hpp"
#include "RType.hpp"
#include "graphic/RessourceManager.hpp"
#include "Serializer.hpp"
#include "Unserializer.hpp"
#include "RequestHandler.hpp"
#include "async/ThreadPool.hpp"

namespace rtype {
	static constexpr char DEBUG_FLAG[] = "-d";

	extern bool IS_DEBUG;


	class Client {
	public:
		static constexpr size_t SERVER_PORT = 4242;
		static constexpr char SERVER_IP[] = "127.0.0.1";
	public:
		Client(ecs::EcsManager &ecsManager, net::NetworkService &netservice);
		~Client();

	public:
		int launch(net::NetworkService &netservice);
		void startGame();
		void initRessources();
		void initGameObjects();
	public:
		void udpSendMove(float x, float y);
		void interpretCommand(rtype::RequestID id, size_t arg = 0);

	private:
		net::TCPSocket _tsocket;
		net::UDPSocket _usocket;
		ecs::EcsManager &_ecsManager;
		graphic::RessourceManager _rsManager;
		SceneManager _sceneManager;
		async::ThreadPool _pool;
		size_t _uid;
		size_t _eid;
		std::unordered_map<size_t, size_t> _entitiesMap;

	private:
		void _udpReceiveLobbyData(size_t gid, size_t nplayers);
		void _udpReceiveGameOver();
		void _udpReceiveSound(size_t sid);
		void _udpReceiveEntityRemove(size_t eid);
		void _udpReceiveID(size_t id);
		void _udpReceiveEntity(size_t eId, size_t textureId, float x, float y);
		void _tcpAssignUid(size_t uid);
		void _tcpSendRequireUid();
		void _tcpSendUdpSetup();
		void _tcpReceiveJoinResp(bool resp);
		void _tcpReceiveLaunch();

		void handleTCPPayloadReception(net::TCPSocket *socket, const char *data, size_t size);
		void handleUDPPayloadReception(net::UDPSocket *socket, const char *data, size_t size);
		void loop();
		void _askForNewUid();

	private:
		class RequestHandler {
		public:
			RequestHandler(Client &server);
			RequestHandler() = delete;
			RequestHandler(RequestHandler &) = default;
			~RequestHandler() = default;
			RequestHandler &operator=(const RequestHandler &) = default;

		public:
			void handleRequest(std::vector<char> &data);
			void handleRequest(net::UDPSocket *socket, std::vector<char> &data);

			template <typename T>
			std::vector<T> extractSingleParam(std::vector<char> &data)
			{
				auto header = rtype::Unserializer::extractHeader(data, *typeid(T).name());
				auto param = rtype::Unserializer::extractParam<T>(data, header.second);
				return param;
			}

		private:
			void _tcpAssignUidWrapper(std::vector<char> &data);
			void _udpReceiveIDWrapper(std::vector<char> &data);
			void _udpReceiveEntityWrapper(std::vector<char> &data);
			void _udpReceiveEntityRemoveWrapper(std::vector<char> &data);
			void _udpReceiveSoundWrapper(std::vector<char> &data);
			void _udpReceiveLobbyDataWrapper(std::vector<char> &data);
			void _tcpReceiveJoinRespWrapper(std::vector<char> &data);

			const std::unordered_map<RequestID,
			std::function<void(std::vector<char> &)>> TCP_WRAPPER = {
				{RequestID::TCP_ASSIGN_UID, [&](std::vector<char> &data) {_tcpAssignUidWrapper(data); }},
				{RequestID::TCP_JOIN_RESP, [&](std::vector<char> &data) { _tcpReceiveJoinRespWrapper(data); }},
				{RequestID::TCP_LAUNCH, [&](std::vector<char> &) { _client._tcpReceiveLaunch(); }},
			};

			const std::unordered_map<RequestID,
			std::function<void(std::vector<char> &)>> UDP_WRAPPER = {
				{RequestID::UDP_SEND_ID, [&](std::vector<char> &data) { _udpReceiveIDWrapper(data); }},
				{RequestID::UDP_SEND_ENTITY, [&](std::vector<char> &data) { _udpReceiveEntityWrapper(data); }},
				{RequestID::UDP_ENTITY_REMOVE, [&](std::vector<char> &data) { _udpReceiveEntityRemoveWrapper(data); }},
				{RequestID::UDP_GAME_OVER, [&](std::vector<char> &) { _client._udpReceiveGameOver(); }},
				{RequestID::UDP_LOBBY_DATA, [&](std::vector<char> &data) { _udpReceiveLobbyDataWrapper(data); }},
			};
			Client &_client;
		};

		RequestHandler _clientWrapper;
	};
}