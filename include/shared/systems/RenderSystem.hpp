//
// EPITECH PROJECT, 2018
// RenderSystem.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <memory>
#include <iostream>
#include "ecs/System.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/WindowComponent.hpp"

namespace rtype {
	class RenderSystem : public ecs::System {
	public:
		RenderSystem(ecs::EcsManager &ecsManager) : ecs::System(ecsManager)
		{}
	public:
		void update(float) final
		{
			if (!_wdCpn)
				_ecsManager.forEachEntity<WindowComponent>(
					[&](const ecs::Entity &, auto wd){
						_wdCpn = wd;
					});
			if (_wdCpn)
				display();	
		}
	private:
		void display()
		{
			_wdCpn->window->clear();
			_ecsManager.forEachEntity<TransformComponent>(
				[&](const ecs::Entity &e, auto pos){
					auto sprC = e.getComponent<SpriteComponent>();
					auto textC = e.getComponent<TextComponent>();
					if (sprC) {
						sprC->sprite.setPosition(pos->x, pos->y);
						_wdCpn->window->draw(sprC->sprite);
					}
					if (textC) {
						if (sprC)
							textC->text.setPosition(pos->x + textC->pos.x,
								pos->y + textC->pos.y);
						else
							textC->text.setPosition(pos->x, pos->y);
						_wdCpn->window->draw(textC->text);
					}
				});
			_wdCpn->window->display();
		}
	private:
		std::shared_ptr<WindowComponent> _wdCpn;
	};
}