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
        DLLoader(const std::string &libpath, const std::string &constructor = CONSTRUCTOR):
            _handle(nullptr), _ctor(nullptr) {
            std::string errorMessage;

            if (libpath != "") {
                _handle = dlopen(libpath.c_str(), RTLD_LAZY | RTLD_LOCAL | RTLD_NODELETE);
                if (!_handle)
                    errorMessage = ": " + std::string(dlerror());
            }
            if (!_handle) {
                errorMessage = "Could not load dynamic library '" + libpath + "'" + errorMessage;
                throw DLLoaderError(errorMessage);
            }
            _ctor = reinterpret_cast<T *(*)()>(dlsym(_handle, constructor.c_str()));
            if (!_ctor)
                throw DLLoaderError(std::string("could not load constructor: ") + dlerror());
        }

        ~DLLoader() {
            if (_handle)
                dlclose(_handle);
        }

        T *getInstance() {
            return (_ctor());
        }

    private:
        void *_handle;
        T *(*_ctor)();
    };

}

#endif /* DLLOADER_HPP_ */
