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
#include <exception>

template <typename T>
class DLLoader {
public:
    DLLoader(const std::string &libpath):
        _handle(dlopen(libpath.c_str(), RTLD_LAZY | RTLD_LOCAL)) {
        if (!_handle)
            throw 1;
    }

    ~DLLoader() {
        dlclose(_handle);
    }

    T *getInstance(const std::string &fct) const {
        return (reinterpret_cast<T *>(dlsym(_handle, fct.c_str())));
    }

private:
    void *_handle;
};

#endif /* DLLOADER_HPP_ */
