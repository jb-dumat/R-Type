//
// EPITECH PROJECT, 2018
// RType
// File description:
// Window.hpp
//

#pragma once
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"
#include "Rectangle.hpp"
#include "Text.hpp"
#include "IWindow.hpp"
#include "IEvent.hpp"

namespace graphic {

    static constexpr unsigned int WIDTH = 1920;
    static constexpr unsigned int HEIGHT = 1080;

    class Window : IWindow, IEvent {
        public:

            Window(std::size_t width, std::size_t height, const std::string title)
                : _width(width), _height(height), _title(title),
                  _window(sf::VideoMode(width, height), _title)
            {
                _events[sf::Event::Closed] = EventType::CLOSED;
                _events[sf::Event::KeyPressed] = EventType::KEYPRESS;
                _events[sf::Event::TextEntered] = EventType::TEXT;
                _keyEvents[sf::Keyboard::Up] = EventType::UP;
                _keyEvents[sf::Keyboard::Down] = EventType::DOWN;
                _keyEvents[sf::Keyboard::Left] = EventType::LEFT;
                _keyEvents[sf::Keyboard::Right] = EventType::RIGHT;
                _keyEvents[sf::Keyboard::Enter] = EventType::ENTER;
                _keyEvents[sf::Keyboard::Escape] = EventType::ESCAPE;
                _keyEvents[sf::Keyboard::BackSpace] = EventType::BACKSPACE;
            }

            Window(const std::string &title)
                : _width(WIDTH), _height(HEIGHT), _title(title),
                  _window(sf::VideoMode(WIDTH, HEIGHT), _title)
            {}

            ~Window() noexcept override
            {_window.close(); }

            inline bool isOpen() override
            { return _window.isOpen(); }

            inline void setMouseCursorVisible(bool visible)
            { _window.setMouseCursorVisible(visible); }

            inline void setFramerateLimit(unsigned int frame)
            { _window.setFramerateLimit(frame); }

            inline void display() override
            { _window.display(); }

            inline void clear() override
            { _window.clear(); }

            inline void setTitle(std::string &title) override
            {
                _title = title;
                _window.setTitle(_title);
            }

            inline void setVerticalSyncState(bool state)
            { _window.setVerticalSyncEnabled(state); }

            inline void draw(const Sprite &sprite)
            { _window.draw(sprite.getSprite()); }

            void draw(const Text &text)
            { _window.draw(text.getText()); }

            inline void draw(const Rectangle &rect)
            { _window.draw(rect.getRectangle()); }

            inline void draw(const std::vector<Sprite> &sprites)
            {
                unsigned int i = 0;

                for (auto it = sprites.begin(); it != sprites.end(); it++, i++) {
                    _window.draw(sprites[i].getSprite());
                }
            }

            EventResult getEvent() override
            {
                // TODO : Maybe put it as an attribute to make a savable queue, only if it's useful.
                // TODO : "Doc: Poll event. Pop the event on top of the event queue, if any, and return it."
                // !TODO
                sf::Event sfEvent{};
                EventResult result{
                    EventType::NONE, 0
                };
                while (_window.pollEvent(sfEvent)) {
                    auto curEvent = _events.find(sfEvent.type);

                    if (curEvent == _events.end()) {
                        continue;
                    }

                    result.type = curEvent->second;

                    if (curEvent->second == EventType::TEXT) {
                        auto unicode = sfEvent.text.unicode;

                        if (unicode < 127 &&
                            unicode != 27 /*ESCAPE*/ &&
                            unicode != '\r' &&
                            unicode != '\b') {
                            result.key = static_cast<char>(unicode);
                        } else
                            result.type = EventType::NONE;
                        return result;
                    }

                    if (curEvent->second == EventType::KEYPRESS) {
                        auto curKeyEvent = _keyEvents.find(sfEvent.key.code);

                        if (curKeyEvent == _keyEvents.end()) {
                            result.type = EventType::NONE;
                        } else {
                            result.type = curKeyEvent->second;
                        }
                        return result;
                    }
                    return result;
                }
                return result;
            }

        private:
            std::size_t _width;
            std::size_t _height;
            std::string _title;
            sf::RenderWindow _window;
            std::map<sf::Event::EventType, EventType> _events;
            std::map<sf::Keyboard::Key, EventType> _keyEvents;
    };
}