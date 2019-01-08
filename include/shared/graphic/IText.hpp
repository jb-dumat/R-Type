/*
** rtype
** Created on 25/11/18.
*/

#pragma once

#include <string>
#include "Color.hpp"
#include "Point.hpp"

namespace graphic
{
	class IText
	{
		public:
			virtual void setString(const std::string &) = 0;
			virtual const std::string getString() const = 0;
			virtual void setColor(const Color &) = 0;
			virtual void setPosition(float x, float y) = 0;
			virtual const Point getPosition() const = 0;
	};
}