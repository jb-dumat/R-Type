//
// EPITECH PROJECT, 2018
// Color.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace graphic {
	enum Color
	{
		RED = 0,
		GREEN = 1,
		BLUE = 2,
		BLACK = 3,
		WHITE = 4,
		YELLOW = 5,
		TRANSP = 6
	};

	// static constexpr char RED[] = "Red";
	// static constexpr char GREEN[] = "Green";
	// static constexpr char BLUE[] = "Blue";
	// static constexpr char BLACK[] = "Black";
	// static constexpr char WHITE[] = "White";
	// static constexpr char YELLOW[] = "Yellow";
	// static constexpr char TRANSP[] = "Transparent";


	static std::unordered_map<int, sf::Color> COLORS = {
		{RED, sf::Color::Red},
		{GREEN, sf::Color::Green},
		{BLUE, sf::Color::Blue}, 
		{BLACK, sf::Color::Black},
		{WHITE, sf::Color::White},
		{YELLOW, sf::Color::Yellow},
		{TRANSP, sf::Color::Transparent}
	};

	static std::unordered_map<Color, sf::Color> getFields() {
		std::unordered_map<Color, sf::Color> fields = {
			{RED, sf::Color::Red},
			{GREEN, sf::Color::Green},
			{BLUE, sf::Color::Blue}, 
			{BLACK, sf::Color::Black},
			{WHITE, sf::Color::White},
			{YELLOW, sf::Color::Yellow},
			{TRANSP, sf::Color::Transparent}
		};
		return fields;
	};
}