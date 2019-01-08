/*
** rtype
** Created on 25/11/18.
*/

#pragma once

#include <cstddef>
#include <utility>
#include "Point.hpp"

namespace graphic
{
	class ISprite
	{
		public:
			virtual void setTextureRect(std::size_t x, std::size_t y,
			                            std::size_t w, std::size_t h) = 0;
			virtual void setScale(float x, float y) = 0;
			virtual void setPosition(float x, float y) = 0;
			virtual Point getPosition() const = 0;
	};
}