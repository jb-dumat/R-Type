/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Unserializer
*/

#include <algorithm>
#include <iostream>

#include "Unserializer.hpp"

const std::string rtype::Unserializer::_extractMagic(std::vector<char> &payload)
{
	static const std::string DEFAULT;
	try {
		std::string magic(payload.begin(), payload.begin() + MAGIC.size());
		payload.erase(payload.begin(), payload.begin() + MAGIC.size());
		return magic;
	} catch (...) {
		std::cerr << "extractMagic: catched an error" << std::endl;
	}
	return DEFAULT;
}

int rtype::Unserializer::_extractSize(std::vector<char> &payload)
{
	try {
		std::vector<char> vSize(payload.begin(), payload.begin() + sizeof(int));
		payload.erase(payload.begin(), payload.begin() + sizeof(int));
		auto iSize = BitsHandler::getFromBytes<int>(vSize);
		return iSize;
	} catch (...) {
		std::cerr << "extractSize: catched an error" << std::endl;
	}
	return 0;
}

char rtype::Unserializer::_extractID(std::vector<char> &payload)
{
	try {
		char id = payload.front();
		payload.erase(payload.begin());
		return id;
	} catch (...) {
		std::cerr << "extractID: catched an error" << std::endl;
	}
	return static_cast<char>(-1);
}

rtype::Unserializer::params_t rtype::Unserializer::extractParams(std::vector<char> &payload)
{
	auto magic = _extractMagic(payload);
	if (magic.compare(MAGIC) != 0) {
		Unserializer::ignorePayload(payload);
		throw std::runtime_error("MAGIC doesn't match.");
	}
	auto size = _extractSize(payload);
	if (size > static_cast<int>(payload.size())) {
		Unserializer::ignorePayload(payload);
		throw std::runtime_error("SIZE doesn't match.");
	}
	auto id = static_cast<RequestID>(_extractID(payload));
	if (id <= RequestID::START && id >= RequestID::END) {
		Unserializer::ignorePayload(payload);
		throw std::runtime_error("REQUEST ID is not valid.");
	}
	return std::make_tuple(magic, size, id, payload);
}

rtype::Unserializer::header_t rtype::Unserializer::extractHeader(std::vector<char> &payload, char type)
{
	if (payload.size() < sizeof(char) + sizeof(int)) {
		ignorePayload(payload);
		throw std::runtime_error("HEADER FORMAT corrupted data.");
	}
	auto htype = rtype::BitsHandler::getFromBytes<char>(payload);
	payload.erase(payload.begin());

	if (htype != type) {
		Unserializer::ignorePayload(payload);
		throw std::runtime_error("HEADER TYPE corrupted data.");
	}

	auto size = rtype::BitsHandler::getFromBytes<int>(payload);
	payload.erase(payload.begin(), payload.begin() + sizeof(int));

	return std::make_pair(type, size);
}

void rtype::Unserializer::ignorePayload(std::vector<char> &payload)
{
	payload.clear();
	std::cerr << "Payload ignored." << std::endl;
}