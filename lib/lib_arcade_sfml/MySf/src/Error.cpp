/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** Error
*/

#include "MySf/Error.hpp"

using namespace MySf;

Error::Error(const std::string &component, const std::string &message):
    _component(component), _message(message)
{}

const char *Error::what() const noexcept
{
    return (_message.c_str());
}

const std::string &Error::getComponent() const noexcept
{
    return (_component);
}
