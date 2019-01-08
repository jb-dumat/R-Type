/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Player
*/

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "RType.hpp"
#include "net/TCPSocket.hpp"
#include "net/UDPSocket.hpp"

namespace rtype {
	struct Player {
		static const size_t UNDEFINED = -1;
		Player(size_t gen) : uid(gen), guid(UNDEFINED), eid(UNDEFINED),
		isHost(false), status(States::IDDLE), tsocket(nullptr), usocket(nullptr) {}

		inline Player &setIddle() { guid = UNDEFINED; status = IDDLE; return *this; }
		inline Player &assign(size_t id, States s) { guid = id; status = s; return *this; }
		inline Player &setHost(bool set) { isHost = set; return *this; }

		size_t uid;
		size_t guid;
		size_t eid;
		bool isHost;
		States status;
//		net::TCPSocket *tsocket;
		std::shared_ptr<net::TCPSocket> tsocket;
		net::UDPSocket *usocket;
//		std::shared_ptr<net::UDPSocket> usocket;

		inline void display() {
			std::cout << "--------------------------" << std::endl
					  << "Player: " << uid << std::endl
					  << "Game: " << guid << std::endl
					  << "Socket tcp at: " << tsocket.get() << std::endl
					  << "Socket udp at: " << usocket << std::endl
					  << "Status: " << status << std::endl
					  << "--------------------------" << std::endl;
		}
	};

	inline bool operator==(const Player &a, const Player &b) { return a.uid == b.uid; }
	inline bool operator!=(const Player &a, const Player &b) { return a.uid != b.uid; }
}