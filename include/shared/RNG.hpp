/*
** rtype
** Created on 21/11/18.
*/

#pragma once

#include <iostream>
#include <random>
#include <map>

namespace rtype
{
	/* SINGLETON */
	class RNG
	{
		public:
			static RNG &getInstance()
			{
				static RNG instance;

				return instance;
			}

		private:
			std::random_device __rd;
			std::mt19937 __mt;
			std::map<std::string, std::uniform_int_distribution<int>> __distributions;

		private:
			RNG() : __mt(__rd()) {}

		public:
			RNG(RNG const &) = delete;
			RNG(RNG &&) = delete;
			RNG &operator=(RNG const &) = delete;
			RNG &operator=(RNG &&) = delete;

			double rand(std::string const &key)
			{
				return __distributions[key](__mt);
			}

			void add_dist(std::string const &key, int min_closed, int max_open)
			{
				__distributions[key] = std::uniform_int_distribution<int>{min_closed, max_open};
			}

			void remove_dist(std::string const &key)
			{
				__distributions.erase(key);
			}
	};
}
