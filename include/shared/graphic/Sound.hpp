//
// EPITECH PROJECT, 2018
// RType
// File description:
// Sound.hpp
//

#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include "SoundBuffer.hpp"

namespace graphic {
  class Sound {
  public:
	  Sound(sf::SoundBuffer &sbuff) : _sbuff(sbuff)
    {
      _sound.setBuffer(_sbuff);
    }

		~Sound() = default;
    
	public:
    inline void play()
    { _sound.play(); }

    inline void pause()
    { _sound.pause(); }

    inline void stop()
    { _sound.pause(); }

    inline void setVolume(float volume)
    { _sound.setVolume(volume); }

    inline void setBuffer(const sf::SoundBuffer &sbuff)
    {
      _sbuff = sbuff;
      _sound.setBuffer(_sbuff);
    }

    inline const sf::SoundSource::Status getStatus() const
    { return _sound.getStatus(); }

	private:
		sf::Sound _sound;
    sf::SoundBuffer &_sbuff;
	};
}