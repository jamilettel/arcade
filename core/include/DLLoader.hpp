/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <dlfcn.h>
#include "CoreError.hpp"

#define CONSTRUCTOR "instance_ctor"
#include <iostream>

namespace arc {

    template <typename T>
    class DLLoader {
    public:
        DLLoader(const std::string &libpath): _handle(nullptr) {
            if (libpath != "")
                _handle = dlopen(libpath.c_str(), RTLD_NOW | RTLD_GLOBAL);
            if (!_handle)
                throw DLLoaderError("Could not load dynamic library '" + libpath + "'");
        }

        ~DLLoader() {
            if (_handle)
                dlclose(_handle);
        }

        T *getInstance(const std::string &constructor = CONSTRUCTOR) {
            T *(*ctor)() = reinterpret_cast<T *(*)()>(dlsym(_handle, constructor.c_str()));

            if (!ctor)
                throw DLLoaderError("could not find function '"+constructor+"' in dynamic lib");
            return (ctor());
        }

    private:
        void *_handle;
    };

}

#endif /* DLLOADER_HPP_ */
