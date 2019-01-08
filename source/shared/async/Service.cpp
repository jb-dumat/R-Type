/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Service
*/

#include <iostream> // REMOVE

#include "async/Service.hpp"

async::Service::Service(MutexQueue<std::function<void()>> &tasks, std::condition_variable &condVar, std::mutex &mutex)
	: AService(), _mutex(mutex), _condVar(condVar), _queue(tasks)
{
	_stop = std::make_shared<std::atomic_bool>(false);
	_thread = std::make_shared<std::thread>(std::thread(std::bind(&Service::run, this)));
	_id = _thread->get_id();
}

void async::Service::run()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	//std::cout << "New service: " << std::this_thread::get_id() << std::endl;
	//std::cout << std::boolalpha << "stop --> [" << _stop << "] - {" << *_stop << "}." << std::endl;

	std::function<void()> task;
	while (!*_stop) {
		{
			std::unique_lock<std::mutex> lock(_mutex);
			//std::cout << "Waiting for work at " << std::this_thread::get_id() << ": " << std::boolalpha << _queue.empty() << " - " << *_stop << "\n";
			_condVar.wait(lock, [&]{ return !_queue.empty() || *_stop;});
			if (*_stop)
				break;
			task = _queue.front();
			_queue.pop();
		}
		task();
	}

	//std::cout << "Stop: " << std::boolalpha << *_stop << std::endl;
}