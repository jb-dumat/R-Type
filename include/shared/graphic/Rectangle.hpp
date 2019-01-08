//
// EPITECH PROJECT, 2018
// Rectangle.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "Color.hpp"
#include "Point.hpp"

namespace graphic {
	class Rectangle {
		public:
			Rectangle(const Point &size = Point(0, 0),
				const Point &pos = Point(0, 0),
				const Color &outLineColor = Color::RED) :
			_rect(sf::Vector2f(size.x, size.y))
			{
				setPosition(pos);
				setOutlineColor(outLineColor);
				setColor(Color::TRANSP);
				setThickness(Rectangle::THICKNESS);
			}
		public:
			inline void setOutlineColor(const Color &color)
			{
				_rect.setOutlineColor(COLORS[color]);
			}
			
			inline void setColor(const Color &color)
			{
				_rect.setFillColor(COLORS[color]);
			}

			inline void setThickness(float thickness)
			{
				_rect.setOutlineThickness(thickness);
			}

			inline void setPosition(float x, float y)
			{
				_rect.setPosition(x, y);
			}

			inline void setPosition(const Point &pos)
			{
				setPosition(pos.x, pos.y);
			}

			inline void setSize(float x, float y)
			{
				_rect.setSize(sf::Vector2f(x, y));
			}

			inline void setSize(const Point &size)
			{
				setSize(size.x, size.y);
			}

			inline const sf::RectangleShape &getRectangle() const
			{
				return _rect;
			}
		private:
			sf::RectangleShape _rect;
		public:
			static constexpr float THICKNESS = 2;
	};
}