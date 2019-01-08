/*
** rtype
** Created on 26/11/18.
*/

#pragma once

#include <string>

namespace graphic
{
	class IWindow
	{
		public:
			virtual ~IWindow() = default;

			virtual bool isOpen() = 0;
			virtual void display() = 0;
			virtual void clear() = 0;
			virtual void setTitle(std::string &title) = 0;
	};
}