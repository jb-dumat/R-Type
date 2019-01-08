//
// EPITECH PROJECT, 2018
// RType
// File description:
// Texture.hpp
//

#pragma once
#include <string>
#include "ITexture.hpp"

namespace graphic {

	class Texture : public ITexture {
	public:
		Texture(const std::string &file) : _file(file)
		{
			if (!_texture.loadFromFile(_file))
				throw std::runtime_error("File Error : \"" + _file + "\"");
		}

		Texture(const Texture &texture) : _texture(texture.getTexture())
		{}
		~Texture() noexcept override = default;

	public:
		inline void setTexture(const std::string &file) override
		{ 
			_file = file;
			if (!_texture.loadFromFile(_file))
				throw std::runtime_error("File Error : \"" + _file + "\"");
		}
		
		inline const sf::Texture &getTexture() const override
		{ return _texture; }

		inline const std::string &getFileFromTexture() const override
		{ return _file; }

	private:
		std::string _file;
		sf::Texture _texture;
	};
}
