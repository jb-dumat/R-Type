//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Font.hpp
//

#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace graphic {

  class Font {

  public:
  	Font(const std::string &file) : _file(file) {
      if (!_font.loadFromFile(_file))
        throw std::runtime_error("File Error : \"" + _file + "\"");
    }

  public:
  	inline void setFont(const std::string &file) {
      if (!_font.loadFromFile(_file))
        throw std::runtime_error("File Error : \"" + _file + "\"");
     _file = file;
    }

  	inline const sf::Font &getFont() const { return _font; };

  private:
  	std::string _file;
    sf::Font _font;
  };

}
