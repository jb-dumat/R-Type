//
// EPITECH PROJECT, 2018
// DLLoader.hpp
// File description:
// Hung Dao Nguyen
//

#pragma once

#include <vector>
#include <memory>
#include <dlfcn.h>
#include <iostream>

namespace hutils {
	template <typename T>
	class DLLoader {
		public :
		~DLLoader()
		{
			for (size_t i = 0; i < _lib_handlers.size(); i++)
				dlclose(_lib_handlers[i]);
		}
		using fn = std::shared_ptr<T> (*)();
		std::shared_ptr<T> getInstance(const std::string &path,
			const std::string &func_name)
		{
			void *lib_handle = dlopen(path.c_str(),
				RTLD_LAZY | RTLD_NODELETE);

			if (!lib_handle) {
				std::cerr <<  dlerror() << std::endl;
				return (nullptr);
			}
			fn load = (fn) dlsym(lib_handle, func_name.c_str());
			if (dlerror() != nullptr) {
				dlclose(lib_handle);
				return (nullptr);
			}
			_lib_handlers.push_back(lib_handle);
			return (load());
		}
	private:
		std::vector<void *>	_lib_handlers;
	};
}