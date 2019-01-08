/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Service
*/

#pragma once
#include <functional>

#include "AService.hpp"
#include "MutexQueue.hpp"

namespace async {
	class Service : public AService {
		public:
			Service(MutexQueue<std::function<void()>> &, std::condition_variable &, std::mutex&);
			Service(const Service &) noexcept = default;
			~Service() noexcept = default;
			Service &operator=(const Service &) noexcept = default;

		public:
			inline bool joinable() override { return _thread->joinable(); };
			inline void join() override { _thread->join(); };
			inline const std::thread::id &getId() const override { return _id; };
			inline void setStop(bool status) override { *_stop = status; };

		private:
			void run();

			std::mutex &_mutex;
			std::condition_variable &_condVar;
			MutexQueue<std::function<void()>> &_queue;
	};
}
