//
// EPITECH PROJECT, 2018
// SystemManager.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <memory>
#include <typeindex>
#include <iostream>
#include <unordered_map>
#include "ISystem.hpp"

namespace ecs {
	class System;

	class EcsManager;

	class SystemManager {
	public:
		SystemManager(EcsManager &ecsManager) noexcept : _ecsManager(ecsManager) {};
		~SystemManager() {};
		SystemManager(const SystemManager &) noexcept = delete;
		SystemManager(SystemManager &&) noexcept = delete;
		SystemManager &operator=(SystemManager &) noexcept = delete;
		SystemManager &operator=(SystemManager &&) noexcept = delete;
	public:
		template <class T>
		void createSystem()
		{
			static_assert(std::is_base_of<System, T>::value,
				"createSystem: received class is not a system.");
			auto typei = std::type_index(typeid(T));
			if (_systems.find(typei) != _systems.end()) {
				std::cerr << "createSystem: System already exists." << std::endl;
				return;
			}
			_systems[typei] = std::make_shared<T>(_ecsManager);			
		}

		template <class ...Systems>
		typename std::enable_if<sizeof...(Systems) == 0>::type createSystems()
		{}

		template <class System, class ...Systems>
		void createSystems()
		{
			createSystem<System>();
			createSystems<Systems...>();
		}

		template <class T>
		std::shared_ptr<ISystem> getSystem()
		{
			static_assert(std::is_base_of<System, T>::value,
				"createSystem: received class is not a system.");
			auto typei = std::type_index(typeid(T));
			if (_systems.find(typei) == _systems.end())
				return nullptr;
			return _systems[typei];
		}

		template <class T>
		void removeSystem()
		{
			static_assert(std::is_base_of<System, T>::value,
				"createSystem: received class is not a system.");
			auto typei = std::type_index(typeid(T));
			if (_systems.find(typei) == _systems.end()) {
				std::cerr << "removeSystem: system not found" << std::endl;
				return;
			}
			_systemsToRemove.push_back(typei);
		}

		template <class ...Systems>
		typename std::enable_if<sizeof...(Systems) == 0>::type removeSystems()
		{}

		template <class System, class ...Systems>
		void removeSystems()
		{
			removeSystem<System>();
			removeSystems<Systems...>();
		}


		void update(float deltaTime);
	private:
		std::unordered_map<std::type_index, std::shared_ptr<ISystem>> _systems;
		EcsManager &_ecsManager;
		std::vector<std::type_index> _systemsToRemove;
	};
}