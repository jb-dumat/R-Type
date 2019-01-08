/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** ThreadPool
*/

#include <iostream> //DELETE
#include <algorithm>

#include "async/ThreadPool.hpp"

async::ThreadPool::ThreadPool(size_t servicesCount)
{
	for (auto i = servicesCount; i > 0; i--)
		makeService();
}

async::ThreadPool::~ThreadPool()
{
	stop();
	_join();
}

void async::ThreadPool::post(const std::function<void()> &task)
{
	_queue.push(task);
	_condVar.notify_one();
};

void async::ThreadPool::_join()
{
	std::for_each(_servicesVector.begin(), _servicesVector.end(), [](std::unique_ptr<AService> &s) {
		std::cout << s->getId() << std::endl;
		if (s->joinable())
			s->join();
	});
}

void async::ThreadPool::stop()
{
	std::for_each(_servicesVector.begin(), _servicesVector.end(), [](std::unique_ptr<AService> &s) { s->setStop(true); });
	_condVar.notify_all();
}

void async::ThreadPool::makeService()
{
	_servicesVector.push_back(std::make_unique<Service>(_queue, _condVar, _mutex));
}