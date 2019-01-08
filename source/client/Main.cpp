/*
** EPITECH PROJECT, 2018
** Main
** File description:
** Main
*/

#include <iostream>
#include <boost/asio.hpp>
#include "SceneManager.hpp"
#include "net/NetworkService.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Entity.hpp"
#include "Client.hpp"
#include "RequestHandler.hpp"

int main(const int ac, const char **av)
{
	std::cout << "Types are: " << std::endl
			  << "char: " << rtype::types::CHAR  << std::endl
			  << "uchar: " << rtype::types::UCHAR << std::endl
			  << "ushort: " << rtype::types::USHORT << std::endl
			  << "short: " << rtype::types::SHORT << std::endl
			  << "lint: " << rtype::types::LINT << std::endl
			  << "llint: " << rtype::types::LLINT << std::endl
			  << "luint: " << rtype::types::LUINT << std::endl
			  << "lluint: " << rtype::types::LLUINT << std::endl
			  << "uint: " << rtype::types::UINT << std::endl
			  << "int: " << rtype::types::INT << std::endl
			  << "float: " << rtype::types::FLOAT << std::endl
			  << "double: " << rtype::types::DOUBLE << std::endl << std::endl;

	std::cout << "TCP Commands are: " << std::endl
			  << "CREATE game: " << 1 << std::endl
			  << "JOIN game*: " << 2 << std::endl
			  << "LEAVE game: " << 3 << std::endl
			  << "LAUNCH game: " << 4 << std::endl
			  << "ADD slot*: " << 5 << std::endl
			  << "DEL slot*: " << 6 << std::endl
			  << "QUIT: " << 7 << std::endl;

	if (ac > 1 && std::string(av[1]) == std::string(rtype::DEBUG_FLAG)) {
		rtype::IS_DEBUG = true;
		std::cout << std::boolalpha;
	}
	std::cout << rtype::IS_DEBUG << std::endl;
	ecs::EcsManager world;
	net::NetworkService netservice;
	rtype::Client client(world, netservice);
	client.launch(netservice);

	boost::asio::io_service::work work(netservice);
	return 0;
}