//
// EPITECH PROJECT, 2018
// TextComponent.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include "Vec2.hpp"
#include "ecs/Component.hpp"
#include "graphic/Text.hpp"

namespace rtype {
	class TextComponent : public ecs::Component {
	public:
		TextComponent(const std::string &_text,
			const graphic::Color &color = graphic::Color::WHITE) :
		text(_text), pos({0, 0})
		{
			text.setColor(color);
		}

		TextComponent(const std::string &_text, graphic::Font *font,
			const graphic::Color &color = graphic::Color::WHITE) :
		text(_text, font), pos({0, 0})
		{
			text.setColor(color);
		}
	public:
		graphic::Text text;
		hutils::Vec2<float> pos;
	};
}