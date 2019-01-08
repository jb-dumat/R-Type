/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** AThreadPool
*/

#pragma once
#include <vector>
#include <functional>
#include <thread>
#include <memory>
#include <unordered_map>
#include <condition_variable>
#include <mutex>

#include "IThreadPool.hpp"
#include "Service.hpp"
#include "MutexQueue.hpp"

namespace async {
	class ThreadPool : public IThreadPool {
		public:
			ThreadPool(size_t);
			ThreadPool(const ThreadPool &) noexcept = default;
			~ThreadPool() noexcept;
			ThreadPool &operator=(ThreadPool &) noexcept = default;

		public:
			void stop() override;
			void post(const std::function<void()> &task) override;
			void makeService() override;

			inline size_t debugQueue() { return _queue.size(); };

		private:
			void _join() override;

			std::vector<std::unique_ptr<AService>> _servicesVector;
			MutexQueue<std::function<void()>> _queue;
			std::condition_variable _condVar;
			std::mutex _mutex;
	};
}