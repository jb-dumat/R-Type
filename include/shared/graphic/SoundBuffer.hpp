//
// EPITECH PROJECT, 2018
// RType
// File description:
// SoundBuffer.hpp
//

#pragma once
#include <string>
#include <SFML/Audio.hpp>

namespace graphic {
  class SoundBuffer {
  public:
  	explicit SoundBuffer(const std::string &file) : _file(file)
    {
      if (!_sbuff.loadFromFile(_file))
        throw std::runtime_error("File Error : \"" + _file + "\"");
    }

  public:
  	inline bool setSoundBuffer(const std::string &file)
    { 
      if (!_sbuff.loadFromFile(_file))
        throw std::runtime_error("File Error : \"" + _file + "\"");
      _file = file;
    }
    inline const sf::SoundBuffer &getSoundBuffer() const
    { return _sbuff; };

  private:
    std::string _file;
    sf::SoundBuffer _sbuff;
  };
}