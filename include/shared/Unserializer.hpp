/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Unserializer
*/

#pragma once
#include <vector>
#include <string>
#include <exception>
#include <tuple>
#include <utility>

#include "BitsHandler.hpp"
#include "RequestHandler.hpp"

namespace rtype {
	struct Unserializer {
		template<typename T>
		static const std::vector<T> extractParam(std::vector<char> &payload, int size)
			{
				if (size > static_cast<int>(payload.size())) {
					ignorePayload(payload);
					throw std::runtime_error("PARAM corrupted data.");
				}
				std::vector<T> param;
				param.reserve(size);

				while (size > 0) {
					param.emplace_back(rtype::BitsHandler::getFromBytes<T>(payload));
					payload.erase(payload.begin(), payload.begin() + sizeof(T));
					size -= 1;
				}
				return param;
			};

		using header_t = std::pair<char, int>;
		static header_t extractHeader(std::vector<char> &payload, char type);

		static const std::string _extractMagic(std::vector<char> &payload);
		static int _extractSize(std::vector<char> &payload);
		static char _extractID(std::vector<char> &payload);

		using params_t = std::tuple<std::string, int, RequestID, std::vector<char>>;
		static params_t extractParams(std::vector<char> &payload);

		static void ignorePayload(std::vector<char> &payload);
	};
}
