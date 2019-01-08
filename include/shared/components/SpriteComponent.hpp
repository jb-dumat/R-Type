//
// EPITECH PROJECT, 2018
// SpriteComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "ecs/Component.hpp"
#include "graphic/Sprite.hpp"

namespace rtype {
	class SpriteComponent : public ecs::Component {
	public:
		SpriteComponent(std::shared_ptr<graphic::Texture> texture) :
		sprite(texture) {}
	
		SpriteComponent(size_t _textureId) : textureId(_textureId)
		{}
	public:
		graphic::Sprite sprite;
		size_t textureId;
	};
}