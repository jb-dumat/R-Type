/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** DataHandler
*/

#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace rtype {
	static const std::string SERVER_IP = "127.0.0.1";
	static const int SERVER_PORT = 4242;
	static const std::string MAGIC = "RTYPE";
	static const std::string SIZE(sizeof(int), '0');
	static const std::string TEMPLATE = MAGIC + SIZE;
	static const size_t START = TEMPLATE.size() - SIZE.size();
	static constexpr char DEFAULT_TYPE = 'c';

	enum class RequestID {
		START = 0,
		TCP_CREAT,
		TCP_JOIN,
		TCP_JOIN_RESP,
		TCP_LEAVE,
		TCP_LAUNCH,
		TCP_ADD_SLOT,
		TCP_DEL_SLOT,
		TCP_QUIT,
		TCP_UDP_SETUP,
		TCP_UDP_SETUP_BACK,
		TCP_ASSIGN_UID,
		TCP_REQUIRE_UID,
		UDP_SEND_UID,
		UDP_CONNECT,
		UDP_MOVE,
		UDP_UPDATE,
		UDP_LOAD,
		UDP_SEND_ID,
		UDP_SEND_ENTITY,
		UDP_ENTITY_REMOVE,
		UDP_GAME_OVER,
		UDP_LOBBY_DATA,
		END
	};

	namespace types {
		static const char CHAR = *typeid(char).name();
		static const char UCHAR = *typeid(unsigned char).name();
		static const char USHORT = *typeid(unsigned short).name();
		static const char SHORT = *typeid(short).name();
		static const char LINT = *typeid(long int).name();
		static const char LLINT = *typeid(long long int).name();
		static const char LUINT = *typeid(long unsigned int).name();
		static const char LLUINT = *typeid(long long unsigned int).name();
		static const char UINT = *typeid(unsigned int).name();
		static const char INT = *typeid(int).name();
		static const char FLOAT = *typeid(float).name();
		static const char DOUBLE = *typeid(double).name();
		static const char BOOL = *typeid(bool).name();
	}
}