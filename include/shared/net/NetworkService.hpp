//
// EPITECH PROJECT, 2018
// NetworkService.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

namespace net {
	class NetworkService : public boost::asio::io_service
	{
	public:
		NetworkService() : boost::asio::io_service()
		{}
		~NetworkService() = default;
	public:
		void run()
		{
			boost::asio::io_service::run();
		}

		void stop()
		{
			boost::asio::io_service::stop();
		}
	};
}