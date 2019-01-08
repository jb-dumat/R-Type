//
// EPITECH PROJECT, 2018
// Entity.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <iostream>

#include "EcsManager.hpp"

namespace ecs {
	class Component;

	class Entity {
	public:
		Entity(EcsManager &ecsManager, size_t _id) : id(_id), _ecsManager(ecsManager)
		{}
		Entity(const Entity &) noexcept = default;
		Entity(Entity &&) noexcept = default;
		Entity &operator=(Entity &&) noexcept = default;
	public:
		template <class T, class ...Args>
		std::shared_ptr<T> emplaceComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value,
				"attachComponent: received parameter is not a component.");
			auto componentManager = _ecsManager.getComponentManager<T>();
			return componentManager->emplaceComponent(*this, std::forward<Args>(args)...);
		}

		template <class T, class ...Args>
		Entity &addComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value,
				"attachComponent: received parameter is not a component.");
			auto componentManager = _ecsManager.getComponentManager<T>();
			componentManager->emplaceComponent(*this, std::forward<Args>(args)...);
			return *this;
		}

		template <class T>
		Entity &attachComponent(T *component)
		{
			static_assert(std::is_base_of<Component, T>::value,
				"attachComponent: received parameter is not a component.");
			auto componentManager = _ecsManager.getComponentManager<T>();
			componentManager->addComponent(*this, component);
			return *this;
		}

		template <class T>
		Entity &detachComponent()
		{
			static_assert(std::is_base_of<Component, T>::value,
				"attachComponent: received parameter is not a component.");
			auto componentManager = _ecsManager.getComponentManager<T>();
			componentManager->removeComponent(*this);
			return *this;
		}

		template <class T>
		Entity &detachComponent(T *)
		{
			static_assert(std::is_base_of<Component, T>::value,
				"attachComponent: received parameter is not a component.");
			auto componentManager = _ecsManager.getComponentManager<T>();
			componentManager->removeComponent(*this);
			return *this;
		}

		template <class T>
		std::shared_ptr<T> getComponent() const
		{
			static_assert(std::is_base_of<Component, T>::value,
				"attachComponent: received parameter is not a component.");
			auto componentManager = _ecsManager.getComponentManager<T>();
			return componentManager->getComponent(*this);
		}

		void remove() const;

	public:
		bool operator==(const Entity &other) noexcept
		{
			return other.id == id;
		}

		bool operator!=(const Entity &other) noexcept
		{
			return !(*this == other);
		}

		Entity &operator=(const Entity &other) noexcept
		{
			id = other.id;
			return *this;
		}
	public:
		// operator== and hash are needed to use Entity as key in map
		friend bool operator==(const Entity& le, const Entity& re)
		{
			return le.id == re.id;
		}

		friend std::hash<ecs::Entity>;
	public:
		friend std::ostream& operator<<(std::ostream &os, const Entity &e)  
		{  
			return os << e.id;  
		}
	public:
		size_t id;
	private:
		EcsManager &_ecsManager;
	};
}

namespace std {
	template<>
	struct hash<ecs::Entity> {
		std::size_t operator()(ecs::Entity const& e) const
		{
			return std::hash<size_t>{}(e.id);
		}
	};
}