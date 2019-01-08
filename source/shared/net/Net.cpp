//
// EPITECH PROJECT, 2018
// Net
// File description:
// Hung Dao Nguyen
//

#include <cstring>      ///< memset
#include <errno.h>      ///< errno
#ifdef _WIN32
	# include <winsock2.h>
	# include <io.h>
#else
	# include <sys/socket.h> ///< socket
	# include <netinet/in.h> ///< sockaddr_in
	# include <arpa/inet.h>  ///< getsockname
	#include <unistd.h>
#endif
#include <iostream>
#include "net/Net.hpp"

std::string net::getMyIP() noexcept
{
	int dns_port = 53;
	struct sockaddr_in serv;
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		std::cerr << "Socket error" << std::endl;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(net::google_dns_server);
	serv.sin_port = htons(dns_port);
	int err = connect(sock, (const struct sockaddr*)&serv, sizeof(serv));
	if (err < 0)
		std::cerr << "Error number: " << errno
		<< ". Error message: " << strerror(errno) << std::endl;
	struct sockaddr_in name;
	socklen_t namelen = sizeof(name);
	err = getsockname(sock, (struct sockaddr*)&name, &namelen);
	char buffer[80];
	inet_ntop(AF_INET, &name.sin_addr, buffer, 80);
	#ifdef _WIN32
		_close(sock);
	#else
		close(sock);
	#endif
	close(sock);
	return std::string(buffer);
}