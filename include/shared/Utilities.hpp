//
// EPITECH PROJECT, 2018
// Utilities.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <random>

namespace hutils {
	inline bool isNumber(const std::string& s)
	{
		return !s.empty() && std::find_if(s.begin(),
			s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
	}

	inline int randInt(int min, int max)
	{
		std::random_device rd;     
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(min, max);

		auto randNumber = uni(rng);
		return randNumber;
	}
}