/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** RequestHandler
*/

#include "Server.hpp"
#include "RequestHandler.hpp"

rtype::Server::RequestHandler::RequestHandler(Server &server) : _server(server)
{
}

void rtype::Server::RequestHandler::handleRequest(std::shared_ptr<Player> player, std::vector<char> &data)
{
	while (data.size() > 0) {
		try {
			auto params = rtype::Unserializer::extractParams(data);
			if (static_cast<std::string>(std::get<0>(params)).compare(MAGIC) != 0)
				return;
			auto id = static_cast<RequestID>(std::get<2>(params));
			data.clear();
			data = std::get<3>(params);
			if (TCP_WRAPPER.find(id)!= TCP_WRAPPER.end())
				TCP_WRAPPER.at(id)(player, data);
		} catch (std::exception &e) {
			std::cerr << "UNSERIALIZER catched an error: " << e.what() << std::endl;
		}
	}
}

void rtype::Server::RequestHandler::handleRequest(net::UDPSocket *socket, std::vector<char> &data)
{
	while (data.size() > 0) {
		try {
			auto params = rtype::Unserializer::extractParams(data);
			if (static_cast<std::string>(std::get<0>(params)).compare(MAGIC) != 0)
				return;
			auto id = static_cast<RequestID>(std::get<2>(params));
			data.clear();
			data = std::get<3>(params);
			if (UDP_WRAPPER.find(id)!= UDP_WRAPPER.end())
				UDP_WRAPPER.at(id)(socket, data);
		} catch (std::exception &e) {
			std::cerr << "UNSERIALIZER catched an error: " << e.what() << std::endl;
		}
	}
}

void rtype::Server::RequestHandler::_tcpJoinWrapper(std::shared_ptr<Player> client, std::vector<char> &data)
{
	_server._tcpJoinGame(client, extractSingleParam<size_t>(data).front());
}

void rtype::Server::RequestHandler::_tcpAddSlotWrapper(std::shared_ptr<Player> client, std::vector<char> &data)
{
	_server._tcpAddSlot(client, extractSingleParam<size_t>(data).front());
}

void rtype::Server::RequestHandler::_tcpDelSlotWrapper(std::shared_ptr<Player> client, std::vector<char> &data)
{
	_server._tcpDelSlot(client, extractSingleParam<size_t>(data).front());
}

void rtype::Server::RequestHandler::_tcpUDPSetupWrapper(std::shared_ptr<Player> client, std::vector<char> &data)
{
	auto ip = extractSingleParam<char>(data);
	auto port = extractSingleParam<int>(data).front();
	_server._tcpUDPSetup(client, ip, port);
}

void rtype::Server::RequestHandler::_udpMoveWrapper(net::UDPSocket *, std::vector<char> &data)
{
	auto uid = extractSingleParam<size_t>(data).front();
	auto x = extractSingleParam<float>(data).front();
	auto y = extractSingleParam<float>(data).front();
	if (_server.getPlayerbyUid(uid))
		_server._udpMove(_server.getPlayerbyUid(uid), x, y);
}