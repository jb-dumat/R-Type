/*
** EPITECH PROJECT, 2018
** RType
** File description:
** Manage commands send by server
*/

#include <algorithm>
#include "CommandManager.hpp"
#include "Server.hpp"

namespace rtype {

    void CommandManager::registerCommand(const std::string &cmd, std::function<void (const std::vector<std::string> &)> func)
    {
        _commandsMap[cmd] = func;
    }

    void CommandManager::ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    void CommandManager::rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    void CommandManager::trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    void CommandManager::readStandardInput()
    {
      std::string cmd;

      while (std::getline(std::cin, cmd)) {
        trim(cmd);
        interpretCommand(cmd);
      } 
    }

    void CommandManager::interpretCommand(const std::string &cmd)
    {
        std::vector<std::string> words;

        parseCommand(cmd, words);
        if (!words.empty())
            executeCommand(words[0], words);
    }

    void CommandManager::parseCommand(const std::string &cmd, std::vector<std::string> &words)
    {
        std::string delim = " ";
        std::string token;
        std::string temp = cmd + " ";
        auto start = 0;
        auto end = temp.find(delim);

        while (end != SIZE_MAX) {
            words.push_back(temp.substr(start, end - start));
            start = end + delim.length();
            end = temp.find(delim, start);
        }
    }
}
