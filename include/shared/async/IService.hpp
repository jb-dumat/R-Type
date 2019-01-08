/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** IService
*/

#pragma once
#include <thread>

namespace async {
	class IService {
		public:
			virtual ~IService() noexcept = default;

		public:
			virtual bool joinable() = 0;
			virtual void join() = 0;
			virtual const std::thread::id &getId() const = 0;
			virtual void setStop(bool) = 0;
	};
}