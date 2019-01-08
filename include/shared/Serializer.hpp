/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Serializer
*/

#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <functional>

#include <iostream>

#include "RequestHandler.hpp"
#include "BitsHandler.hpp"

namespace rtype {
	struct Serializer {
		static std::pair<const char*, size_t> makeRequest(const std::vector<char> &req)
		{
			char *data = new char[req.size()];
			int len = 0;
			for (auto &it : req) {
				// printf("%x ", it);
				data[len] = it;
				len++;
			}
			// printf("\n");
			return std::make_pair(data, len);
		}


		static void _insertSize(std::vector<char> &payload, int size)
		{
			auto bytes = rtype::BitsHandler::getAsBytes(size);
			size_t index = START;
			for (auto &it : bytes) {
				*(payload.begin() + index) = it;
				index += 1;
			}
		}

		template<typename T>
		static int _insertBytes(std::vector<char> &payload, T data)
		{
			auto bytes = rtype::BitsHandler::getAsBytes(data);
			int countedBytes = 0;

			for (auto &it : bytes) {
				payload.push_back(it);
				countedBytes += 1;
			}
			return countedBytes;
		}

		inline static int handleArgs(std::vector<char> &)
		{
			return 0;
		}

		template<typename T, typename... Args>
		static int handleArgs(std::vector<char> &payload, const std::vector<T> var, Args&&... args)
		{
			int countedBytes = 0;
			countedBytes += _insertDataHeader(payload, var);
			for (auto &it : var)
				countedBytes += _insertBytes(payload, it);
			countedBytes += handleArgs(payload, args...);
			return countedBytes;
		}

		template<typename T, typename... Args>
		static int handleArgs(std::vector<char> &payload, T var, Args&&... args)
		{
			int countedBytes = 0;
			countedBytes += _insertDataHeader(payload, var);
			countedBytes += _insertBytes(payload, var);
			countedBytes += handleArgs(payload, args...);
			return countedBytes;
		}

		template<typename T, typename... Args>
		static const std::vector<char> makePayload(RequestID id, T var, Args&&... args)
		{
			std::vector<char> payload(TEMPLATE.begin(), TEMPLATE.end());

			int countedBytes = 1;
			payload.emplace_back(static_cast<char>(id));

			countedBytes += _insertDataHeader(payload, var);
			countedBytes += _insertBytes(payload, var);
			countedBytes += handleArgs(payload, args...);

			// std::cout << "BYTES: " << countedBytes << std::endl;
			_insertSize(payload, countedBytes);
			return payload;
		}

		template<typename T, typename... Args>
		static const std::vector<char> makePayload(RequestID id, const std::vector<T> var, Args&&... args)
		{
			std::vector<char> payload(TEMPLATE.begin(), TEMPLATE.end());

			int countedBytes = 1;
			payload.emplace_back(static_cast<char>(id));

			countedBytes += _insertDataHeader(payload, var);
			for (auto &it : var)
				countedBytes += _insertBytes(payload, it);
			countedBytes += handleArgs(payload, args...);

			// std::cout << "BYTES: " << countedBytes << std::endl;
			_insertSize(payload, countedBytes);
			return payload;
		}

		static const std::vector<char> makePayload(RequestID id)
		{
			std::vector<char> payload(TEMPLATE.begin(), TEMPLATE.end());
			payload.emplace_back(static_cast<char>(id));

			// std::cout << "BYTES: " << 0 << std::endl;
			_insertSize(payload, 1);
			return payload;
		}

		template<typename T>
		static int _insertDataHeader(std::vector<char> &payload, const std::vector<T> &var)
		{
			int countedBytes = 1;
			payload.emplace_back(*typeid(T).name());
			countedBytes += _insertBytes(payload, static_cast<int>(var.size()));
			return countedBytes;
		}

		template<typename T>
		static int _insertDataHeader(std::vector<char> &payload, T)
		{
			int countedBytes = 1;
			payload.emplace_back(*typeid(T).name());
			countedBytes += _insertBytes(payload, 1);
			return countedBytes;
		}
	};
}
