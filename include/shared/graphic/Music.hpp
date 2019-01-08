//
// EPITECH PROJECT, 2018
// RType
// File description:
// Music.hpp
//

#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include "IMusic.hpp"

namespace graphic
{
	class Music : IMusic
	{
		public:
			Music(const std::string &file)
			{
				if (!_music.openFromFile(file)) {
					throw std::runtime_error("File not found: \"" + file + " \"");
				}
			}

			~Music() override = default;

		public:
			inline void play() override
			{ _music.play(); }

			inline void pause() override
			{ _music.pause(); }

			inline void stop() override
			{ _music.pause(); }

			inline void setVolume(float volume) override
			{ _music.setVolume(volume); }

		private:
			sf::Music _music;
	};
}