/*
** rtype
** Created on 27/11/18.
*/

#pragma once

#include <functional>
#include "Vec2.hpp"

namespace rtype
{
	struct ButtonInfo {
		std::string text;
		hutils::Vec2<float> pos;
		hutils::Vec2<float> textPos;
		std::function<void ()> onSelect;
	};

    class IScene
    {
        public:
            virtual ~IScene() = default;

            virtual void load() = 0;
            virtual void unload() = 0;
    };
}