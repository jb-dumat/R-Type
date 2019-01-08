//
// EPITECH PROJECT, 2018
// RType
// File description:
// Point.hpp
//

#pragma once

#include "Vec2.hpp"

namespace Keyboard {
	enum Key {
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ESC,
		SPACE
	};
}

namespace graphic {

	using Point = hutils::Vec2<float>;
}
