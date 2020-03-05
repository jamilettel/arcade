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
#include "Error.hpp"

template <typename T>
class DLLoader {
public:
    DLLoader(const std::string &libpath):
        _handle(dlopen(libpath.c_str(), RTLD_LAZY | RTLD_LOCAL)) {
        if (!_handle)
            throw DLLoaderError("Could not load dynamic library '" + libpath + "'");
    }

    ~DLLoader() {
        dlclose(_handle);
    }

    T *getInstance(const std::string &fct) const {
        T *(*ctor)() = reinterpret_cast<T *(*)()>(dlsym(_handle, fct.c_str()));

        return (ctor());
    }

private:
    void *_handle;
};

#endif /* DLLOADER_HPP_ */
