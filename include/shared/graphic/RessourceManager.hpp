//
// EPITECH PROJECT, 2018
// RType
// File description:
// RessourceManager.hpp
//

#pragma once
#include <memory>
#include <iostream>
#include "Texture.hpp"
#include "Font.hpp"
#include "Music.hpp"
#include "SoundBuffer.hpp"

namespace graphic {
  class RessourceManager {
  public:
    RessourceManager() = default;
    ~RessourceManager() = default;
  public:
    inline std::shared_ptr<Texture> getTexture(const std::size_t id)
    {
      if (_textures.find(id) == _textures.end()) {
        std::cerr << "getTexture: Texture not found." << std::endl;
        return nullptr;
      }
      return _textures[id];
    }

    inline Font *getFont(const std::size_t id)
    {
      if (_fonts.find(id) == _fonts.end()) {
        std::cerr << "getFont: Font not found." << std::endl;
        return nullptr;
      }
      return _fonts[id];
    }

    inline std::shared_ptr<Music> getMusic(const std::size_t id)
    {
      if (_musics.find(id) == _musics.end()) {
        std::cerr << "getMusic: Music not found." << std::endl;
        return nullptr;
      }
      return _musics[id];
    }

    inline std::shared_ptr<SoundBuffer> getSoundBuffer(const std::size_t id)
    {
      if (_soundBuffers.find(id) == _soundBuffers.end()) {
        std::cerr << "getSoundBuffer: SoundBuffer not found." << std::endl;
        return nullptr;
      }
      return _soundBuffers[id];
    }
  public:
    inline Font *createFont(const std::size_t id, const std::string &file)
    {
      if (_fonts.find(id) != _fonts.end()) { 
        std::cerr << "CreateFont: Font Id already exists." << std::endl; 
        return nullptr;
      }
      _fonts.emplace(id, new Font(file));
      return _fonts[id];
    }

    inline std::shared_ptr<Texture> createTexture(const std::size_t id, const std::string &file)
    {
      if (_textures.find(id) != _textures.end()) { 
        std::cerr << "CreateTexture: Texture Id already exists." << std::endl; 
        return nullptr;
      }
      _textures.emplace(id, std::make_shared<Texture>(file));
      return _textures[id];
    }

    inline std::shared_ptr<Music> createMusic(const std::size_t id, const std::string &file)
    {
      if (_musics.find(id) != _musics.end()) { 
        std::cerr << "CreateMusic: Music Id already exists." << std::endl; 
        return nullptr;
      }
      _musics.emplace(id, std::make_shared<Music>(file));
      return _musics[id];
    }

    inline std::shared_ptr<SoundBuffer> createSoundBuffer(const std::size_t id, const std::string &file)
    {
      if (_soundBuffers.find(id) != _soundBuffers.end()) { 
        std::cerr << "CreateSoundBuffer: SoundBuffer Id already exists." << std::endl; 
        return nullptr;
      }
      _soundBuffers.emplace(id, std::make_shared<SoundBuffer>(file));
      return _soundBuffers[id];
    }
  public:
    inline void deleteFont(const std::size_t id)
    {
      if (_fonts.find(id) == _fonts.end()) { 
        std::cerr << "CreateFont: Font doesn't exist." << std::endl; 
        return;
      }
      _fonts.erase(id);
      return;
    }

    inline void deleteTexture(const std::size_t id)
    {
      if (_textures.find(id) == _textures.end()) { 
        std::cerr << "DeleteTexture: Textures doesn't exist." << std::endl; 
        return;
      }
      _textures.erase(id);
      return;
    }

    inline void deleteMusic(const std::size_t id)
    {
      if (_musics.find(id) == _musics.end()) { 
        std::cerr << "DeleteMusic: Music doesn't exist." << std::endl; 
        return;
      }
      _musics.erase(id);
      return;
    }

    inline void deleteSoundBuffers(const std::size_t id)
    {
      if (_soundBuffers.find(id) == _soundBuffers.end()) { 
        std::cerr << "DeleteSoundBuffer: SoundBuffer doesn't exist." << std::endl; 
        return;
      }
      _soundBuffers.erase(id);
      return;
    }

  private:
    std::unordered_map<std::size_t, Font *> _fonts;
    std::unordered_map<std::size_t, std::shared_ptr<Texture>> _textures;
    std::unordered_map<std::size_t, std::shared_ptr<Music>> _musics;
    std::unordered_map<std::size_t, std::shared_ptr<SoundBuffer>> _soundBuffers;
  };
}