/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Server
*/

#pragma once
#include <unordered_map>
#include <boost/bind.hpp>
#include <memory>
#include <vector>
#include <list>

#include "net/Net.hpp"
#include "net/UDPSocket.hpp"
#include "net/TCPSocket.hpp"
#include "async/ThreadPool.hpp"
#include "components/MonsterComponent.hpp"
#include "DLLoader.hpp"
#include "RequestHandler.hpp"
#include "Serializer.hpp"
#include "Unserializer.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "CommandManager.hpp"

namespace rtype {
	class Server {
	public:
		Server() = delete;
		Server(net::NetworkService &netService);
		Server(Server &) = default;
		~Server();
		Server &operator=(const Server &) = default;

	public:
		void _serverLoop();
		void loadMonster(const std::string &monsterFile);
		std::shared_ptr<Player> getPlayerbySocket(net::ISocket *socket);
		std::shared_ptr<Player> getPlayerbyUid(size_t uid);

	private:
		void _tcpSendLaunch(size_t guid);
		void _tcpSendJoinResp(net::ISocket *socket, char resp);
		void _tcpCreateGame(std::shared_ptr<Player> client);
		void _tcpJoinGame(std::shared_ptr<Player> client, size_t uidGame);
		void _tcpLeaveGame(std::shared_ptr<Player> client);
		void _tcpLaunchGame(std::shared_ptr<Player> client);
		void _tcpAddSlot(std::shared_ptr<Player> client, size_t nb);
		void _tcpDelSlot(std::shared_ptr<Player> client, size_t nb);
		void _tcpQuit(const std::shared_ptr<Player> client);
		void _tcpUDPSetup(std::shared_ptr<Player> client, const std::vector<char> &ip, int port);
		void _tcpUDPSetupBack(net::ISocket *socket, const std::string &ip, int port);
		void _tcpRequireUid(std::shared_ptr<Player> client);
		void _tcpAssignUid(net::ISocket *socket, size_t uid);
		void _udpMove(std::shared_ptr<Player> player, float x, float y);
	public:
		void handlePlayerConnection(net::ISocket *socket);
		void handleTCPPayloadReception(net::TCPSocket *socket, const char *data, size_t size = 0);
		void handleUDPPayloadReception(net::UDPSocket *socket, const char *data, size_t size = 0);
		void handlePlayerDisconnection(net::ISocket *socket);
	public:
		std::unordered_map<size_t, std::shared_ptr<Player>> _players;
		std::unordered_map<size_t, std::unique_ptr<Game>> _games;
		std::shared_ptr<std::vector<std::shared_ptr<MonsterComponent>>> _monsters;
		hutils::DLLoader<MonsterComponent> _dlloader;
		net::NetworkService &_netService;
		std::unique_ptr<CommandManager> _cmdManager;
		std::unique_ptr<async::IThreadPool> _pool;

		net::TCPSocket _tsocket;
		net::UDPSocket _usocket;

		struct genuid {
			size_t uid = 0;
		} gen;

	private:
		class RequestHandler {
		public:
			RequestHandler(Server &server);
			RequestHandler() = delete;
			RequestHandler(RequestHandler &) = default;
			~RequestHandler() = default;
			RequestHandler &operator=(const RequestHandler &) = default;

		public:
			void handleRequest(std::shared_ptr<Player> player, std::vector<char> &data);
			void handleRequest(net::UDPSocket *socket, std::vector<char> &data);

				template <typename T>
			std::vector<T> extractSingleParam(std::vector<char> &data) {
				auto header = rtype::Unserializer::extractHeader(data, *typeid(T).name());
				auto param = rtype::Unserializer::extractParam<T>(data, header.second);
				return param;
			}

		private:
			void _tcpJoinWrapper(std::shared_ptr<Player> client, std::vector<char> &data);
			void _tcpAddSlotWrapper(std::shared_ptr<Player> client, std::vector<char> &data);
			void _tcpDelSlotWrapper(std::shared_ptr<Player> client, std::vector<char> &data);
			void _tcpUDPSetupWrapper(std::shared_ptr<Player> client, std::vector<char> &data);

			void _udpMoveWrapper(net::UDPSocket *socket, std::vector<char> &data);

			const std::unordered_map<RequestID, std::function<void(std::shared_ptr<Player> , std::vector<char>&)>> TCP_WRAPPER = {
				{ RequestID::TCP_CREAT, [&](std::shared_ptr<Player> client, std::vector<char>&){ _server._tcpCreateGame(client); } },
				{ RequestID::TCP_LEAVE, [&](std::shared_ptr<Player> client, std::vector<char>&){ _server._tcpLeaveGame(client); } },
				{ RequestID::TCP_QUIT, [&](std::shared_ptr<Player> client, std::vector<char>&){ _server._tcpQuit(client); } },
				{ RequestID::TCP_JOIN, [&](std::shared_ptr<Player> client, std::vector<char> &data){ _tcpJoinWrapper(client, data); } },
				{ RequestID::TCP_LAUNCH, [&](std::shared_ptr<Player> client, std::vector<char> &){ _server._tcpLaunchGame(client); } },
				{ RequestID::TCP_ADD_SLOT, [&](std::shared_ptr<Player> client, std::vector<char> &data){ _tcpAddSlotWrapper(client, data); } },
				{ RequestID::TCP_DEL_SLOT, [&](std::shared_ptr<Player> client, std::vector<char> &data){ _tcpDelSlotWrapper(client, data); } },
				{ RequestID::TCP_UDP_SETUP, [&](std::shared_ptr<Player> client, std::vector<char> &data){ _tcpUDPSetupWrapper(client, data); } },
				{ RequestID::TCP_UDP_SETUP, [&](std::shared_ptr<Player> client, std::vector<char> &){ _server._tcpRequireUid(client); } },
			};

			const std::unordered_map<RequestID, std::function<void(net::UDPSocket*, std::vector<char>&)>> UDP_WRAPPER = {
				{ RequestID::UDP_MOVE, [&](net::UDPSocket *socket, std::vector<char> &data){ _udpMoveWrapper(socket, data); } },
			};

			Server &_server;
		};

		RequestHandler _serverWrapper;
	};
}