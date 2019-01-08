/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** RequestHandler
*/

#include "Client.hpp"

rtype::Client::RequestHandler::RequestHandler(Client &client) : _client(client)
{
}

void rtype::Client::RequestHandler::handleRequest(std::vector<char> &data)
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
				TCP_WRAPPER.at(id)(data);
		} catch (std::exception &e) {
			std::cerr << "UNSERIALIZER catched an error: " << e.what() << std::endl;
		}
	}
}

void rtype::Client::RequestHandler::handleRequest(net::UDPSocket *, std::vector<char> &data)
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
				UDP_WRAPPER.at(id)(data);
		} catch (std::exception &e) {
			std::cerr << "UNSERIALIZER catched an error: " << e.what() << std::endl;
		}
	}
}

void rtype::Client::RequestHandler::_tcpAssignUidWrapper(std::vector<char> &data)
{
	auto uid = extractSingleParam<size_t>(data).front();
	_client._tcpAssignUid(uid);
}

void rtype::Client::RequestHandler::_udpReceiveIDWrapper(std::vector<char> &data)
{
	auto id = extractSingleParam<size_t>(data).front();
	_client._udpReceiveID(id);
}

void rtype::Client::RequestHandler::_udpReceiveEntityWrapper(std::vector<char> &data)
{
	auto id = extractSingleParam<size_t>(data).front();
	auto textureId = extractSingleParam<size_t>(data).front();
	auto x = extractSingleParam<float>(data).front();
	auto y = extractSingleParam<float>(data).front();
	_client._udpReceiveEntity(id, textureId, x, y);
}

void rtype::Client::RequestHandler::_udpReceiveEntityRemoveWrapper(std::vector<char> &data)
{
	auto eid = extractSingleParam<size_t>(data).front();
	_client._udpReceiveEntityRemove(eid);
}

void rtype::Client::RequestHandler::_udpReceiveSoundWrapper(std::vector<char> &data)
{
	auto sid = extractSingleParam<size_t>(data).front();
	_client._udpReceiveSound(sid);
}

void rtype::Client::RequestHandler::_udpReceiveLobbyDataWrapper(std::vector<char> &data)
{
	std::cout << "lobby" << std::endl;
	auto gid = extractSingleParam<size_t>(data).front();
	auto nplayers = extractSingleParam<size_t>(data).front();

	std::cout << "Lobby - gid: " << gid << " -- np: " << nplayers << std::endl;

	_client._udpReceiveLobbyData(gid, nplayers);
}

void rtype::Client::RequestHandler::_tcpReceiveJoinRespWrapper(std::vector<char> &data)
{
	std::cout << "rec" << std::endl;
	auto resp = extractSingleParam<char>(data).front();

	std::cout << "Resp: " << resp << std::endl;

	_client._tcpReceiveJoinResp(static_cast<bool>(resp));
}