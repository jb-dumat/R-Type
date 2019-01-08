/*
** EPITECH PROJECT, 2018
** RType
** File description:
** Manage command send by server header
*/

#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

namespace rtype {
    class CommandManager {
    
    enum CommandID {
        LOAD = 0,
        SHOW
    };

    public:
        CommandManager() = default;
        ~CommandManager() = default;
    
        void readStandardInput();
        void interpretCommand(const std::string &cmd);
        void parseCommand(const std::string &cmd, std::vector<std::string> &words);
        void executeCommand(const std::string &key, std::vector<std::string> &args)
        {
		    if (_commandsMap.find(key) != _commandsMap.end())
                _commandsMap[key](args);
	    }
        void registerCommand(const std::string &cmd,
            std::function<void (const std::vector<std::string> &)> func);
    
     private:
        void rtrim(std::string &s);
        void ltrim(std::string &s);
        void trim(std::string &s);
        std::unordered_map<std::string,
        std::function<void (const std::vector<std::string> &)>> _commandsMap;
    };
}