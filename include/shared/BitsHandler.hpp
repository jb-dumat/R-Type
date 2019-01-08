/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** BitsHandler
*/

#pragma once
#include <vector>
#include <cstring>

namespace rtype {
	class BitsHandler {
	public:
		BitsHandler() = default;
		~BitsHandler() = default;

	private:
		template<typename T> union Converter {
			char b[sizeof(T)];
			T t;
		};

	public:
		template<typename T>
		static std::vector<char> getAsBytes(T n)
			{
				std::vector<char> bytes(sizeof(T), 0);
				Converter<T> conv;

				memset(&conv.b, 0, sizeof(T));
				conv.t = n;

/*				printf("BITSHANDLER: {%lu} ", sizeof(conv.b));
				int i = 0;
				while (conv.b[i]) {
					printf("%x ", conv.b[i]);
					i += 1;
				}
				std::cout << std::endl;

*/				for (auto i = 0; i != sizeof(T); i++)
					bytes[i] = conv.b[i];
				return bytes;
			}

		template<typename T>
		static T getFromBytes(const std::vector<char> &bytes)
			{
				Converter<T> conv;
				char buf[sizeof(T)];
				memset(&conv.b, 0, sizeof(conv.b));
				size_t i = 0;

				for (auto &it : bytes) {
					buf[i++] = it;
					if (i > sizeof(T))
						break;
				}
				std::memcpy(conv.b, buf, sizeof(T));
				return conv.t;
			}
	};
}
