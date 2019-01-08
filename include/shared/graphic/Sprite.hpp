//
// EPITECH PROJECT, 2018
// rtype
// File description:
// header
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Texture.hpp"
#include "Point.hpp"
#include "ISprite.hpp"

namespace graphic {
	class Sprite : public ISprite {
	public:
		Sprite(std::shared_ptr<Texture> t) : _texture(t)
		{
			_sprite.setTexture(_texture->getTexture());
		}

		Sprite() = default;

		~Sprite() noexcept = default;

	public:
		inline void setTexture(std::shared_ptr<Texture> t)
		{
			_texture = t;
			_sprite.setTexture(_texture->getTexture());
		}

		inline void setTextureRect(std::size_t x, std::size_t y,
			std::size_t w, std::size_t h) override
		{ _sprite.setTextureRect(sf::IntRect(x, y, w, h)); }

		inline void move(float x, float y)
		{	
			_pos.x = x;
			_pos.y = y;
			_sprite.move(x, y);
		}

		inline void move(const Point &translation)
		{
			sf::Vector2f offset(translation.x, translation.y);  

			_pos = translation;
			_sprite.move(offset);
		}

		inline void setPosition(float x, float y) override
		{ _sprite.setPosition(x, y); }

		inline void setRotation(float rotation)
		{	_sprite.setRotation(rotation); }

		inline void setScale(float x, float y) override
		{	_sprite.setScale(x, y); }

		inline void setScale(const Point &pos)
		{
			sf::Vector2f vpos(pos.x, pos.y);

			_sprite.setScale(vpos);
		}

		inline Point getPosition() const override
		{
			auto pos = _sprite.getPosition();

			return Point((float)pos.x, (float)pos.y);
		}

		inline const sf::Sprite &getSprite() const
		{ return _sprite; }

	private:
		sf::Sprite _sprite;
		std::shared_ptr<Texture> _texture;
		Point _pos;
	};
} 