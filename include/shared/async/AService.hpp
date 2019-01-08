/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** AService
*/

#pragma once
#include <condition_variable>
#include <atomic>
#include <memory>
#include <mutex>

#include "IService.hpp"

namespace async {
	class AService : public IService {
		protected:
			AService() noexcept = default;
		public:
			virtual ~AService() noexcept = default;

		public:
			virtual bool joinable() = 0;
			virtual void join() = 0;
			virtual const std::thread::id &getId() const = 0;
			virtual void setStop(bool) = 0;

		protected:
			std::shared_ptr<std::atomic_bool> _stop;
			std::thread::id _id;
			std::shared_ptr<std::thread> _thread;
	};
}