//
// EPITECH PROJECT, 2018
// RType.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include "Action.hpp"

namespace rtype {
	static constexpr int FAIL_CODE = 84;
	static constexpr int SUCCESS_CODE = 0;
	static constexpr int WINDOW_WIDTH = 960;
	static constexpr int WINDOW_HEIGHT = 720;
	static constexpr int FRAME_RATE = 120;
	static constexpr char WINDOW_TITLE[] = "RTYPE";
	static constexpr char GET_MONSTER_FUNC[] = "getMonster";

	enum States {
		IDDLE = 0,
		LOBBY,
		GAME
	};

	namespace TEXTURE {
		enum TEXTURE {
			BUTTON = 0,
			BUTTON_SELECTED,
			FRAME,
			SPACESHIP,
			SPACESHIP2,
			SPACESHIP3,
			SPACESHIP4,
			BULLET,
			BULLET2,
			BULLET3,
			BULLET4,
			ENEMY,
			ENEMY2,
			ENEMY3,
			STAR,
			STAR2,
			ASTEROID,
			ASTEROID2,
			EMPTY,
		};
	}

	namespace FONT {
		enum {
			ARIAL = 0,
			GALIVER
		};
	}

	namespace GO {
		enum {
			BUTTON = 0,
			SPACESHIP
		};
	}

	static std::unordered_map<int, std::string> TEXTURES = {
		{TEXTURE::BUTTON, "./assets/button.png"},
		{TEXTURE::BUTTON_SELECTED, "./assets/button_selected.png"},
		{TEXTURE::FRAME, "./assets/frame.png"},
		{TEXTURE::SPACESHIP, "./assets/spaceship1.png"},
		{TEXTURE::SPACESHIP2, "./assets/spaceship2.png"},
		{TEXTURE::SPACESHIP3, "./assets/spaceship3.png"},
		{TEXTURE::SPACESHIP4, "./assets/spaceship4.png"},
		{TEXTURE::BULLET, "./assets/bullet.png"},
		{TEXTURE::BULLET2, "./assets/bullet2.png"},
		{TEXTURE::BULLET3, "./assets/bullet3.png"},
		{TEXTURE::BULLET4, "./assets/bullet4.png"},
		{TEXTURE::ENEMY, "./assets/enemy1.png"},
		{TEXTURE::ENEMY2, "./assets/enemy2.png"},
		{TEXTURE::ENEMY3, "./assets/enemy3.png"},
		{TEXTURE::STAR, "./assets/star.png"},
		{TEXTURE::STAR2, "./assets/star2.png"},
		{TEXTURE::ASTEROID, "./assets/asteroid.png"},
		{TEXTURE::ASTEROID2, "./assets/asteroid2.png"},
        {TEXTURE::EMPTY, "./assets/empty.png"},
	};

	static std::unordered_map<int, std::string> FONTS = {
		{FONT::ARIAL, "./assets/fonts/arial.ttf"},
		{FONT::GALIVER, "./assets/fonts/GALSB.ttf"}
	};

	inline std::vector<Action> parseActions(const std::string &file)
	{
		std::ifstream infile(file);
		std::vector<Action> actions;
		std::string line;
		while (std::getline(infile, line)) {
			Action a;
			std::istringstream iss(line);
			iss >> a.type >> a.startAt >> a.x >> a.y >> a.speed;
			actions.push_back(a);
		}
		return actions;
	}
}