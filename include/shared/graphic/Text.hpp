//
// EPITECH PROJECT, 2018
// Rtype
// File description:
// Text.hpp
//

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Font.hpp"
#include "IText.hpp"
#include "Point.hpp"

namespace graphic {

    class Text : public IText {
        public:
            Text(const std::string &text) : _size(30)
            {
                _sfText.setString(text);
                _colorMap = getFields();
            }

            Text(const std::string &text, Font *font) : _font(font), _size(30)
            {
                _sfText.setString(text);
                _sfText.setFont(font->getFont());
                _colorMap = getFields();
            }

            Text(const Text &text) : _sfText(text.getString(), (text.getFont())->getFont(), text.getCharacterSize())
            {
                auto pos = text.getPosition();
                _colorMap = getFields();

                _sfText.setFillColor(_colorMap[text.getColor()]);
                _sfText.setPosition(pos.x, pos.y);
            }

            ~Text() noexcept = default;

            inline void setFont(Font *font)
            {
                _font = font;
                _sfText.setFont(font->getFont());
            }

            inline Font *getFont() const
            {
                return _font;
            }

            inline void setString(const std::string &text) override
            {
                _sfText.setString(text);
            };

            inline const std::string getString() const override
            {
                return _sfText.getString();
            }

            inline void setColor(const Color &color) override
            {
                _color = color;
                _sfText.setFillColor(_colorMap[_color]);
            }

            inline Color getColor() const
            { return _color; }

            inline void setPosition(float x, float y) override
            {
                _sfText.setPosition(x, y);
                _pos.x = x;
                _pos.y = y;
            }

            inline const Point getPosition() const override
            {
                auto pos = _sfText.getPosition();

                return Point((float)pos.x, (float)pos.y);
            }

            inline const sf::Text &getText() const
            { return _sfText; }

            inline void setPosition(const Point &pos)
            { 
              _pos = pos;
              _sfText.setPosition(_pos.x, _pos.y);
            }

            inline void setRotation(float rot)
            { _sfText.setRotation(rot); }

            inline void setScale(float x, float y)
            { _sfText.setScale(x, y); }

            inline void setOrigin(float x, float y)
            { _sfText.setOrigin(x, y); }

            inline void setOrigin(const Point &pos)
            { _sfText.setOrigin(pos.x, pos.y); }

            inline void setCharacterSize(unsigned int size)
            { 
              _size = size;
              _sfText.setCharacterSize(_size);
            }

            inline unsigned int getCharacterSize() const
            { return _size; }

        private:
            sf::Text _sfText;
            Font *_font;
            Point _pos;
            Color _color;
            unsigned int _size;
            std::unordered_map<Color, sf::Color> _colorMap;
    };
}
