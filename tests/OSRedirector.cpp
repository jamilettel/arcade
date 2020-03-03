/*
** EPITECH PROJECT, 2020
** OS Redirector
** File description:
** tests
*/

#include "OSRedirector.hpp"

OSRedirector::OSRedirector(std::ostream &c) : _c(c) {
    _backup = _c.rdbuf();
    _c.rdbuf(_oss.rdbuf());
}

OSRedirector::~OSRedirector() {
    _c.rdbuf(_backup);
}

const std::string OSRedirector::getContent() {
    _oss << std::flush;
    return _oss.str();
}
