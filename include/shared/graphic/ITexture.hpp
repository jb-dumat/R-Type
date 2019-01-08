/*
** rtype
** Created on 26/11/18.
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>

namespace graphic
{
	class ITexture
	{
		public:
			virtual ~ITexture() = default;

			virtual void setTexture(const std::string &file) = 0;
			virtual const sf::Texture &getTexture() const = 0;
			virtual const std::string &getFileFromTexture() const = 0;
	};
}