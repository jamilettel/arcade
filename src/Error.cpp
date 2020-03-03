/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Error
*/

#include "Error.hpp"

ArcadeError::ArcadeError(const std::string &component, const std::string &message):
    _component(component), _message(message)
{}

const char *ArcadeError::what() const noexcept
{
    return (_message.c_str());
}

const std::string &ArcadeError::getComponent() const noexcept
{
    return (_component);
}

DLLoaderError::DLLoaderError(const std::string &message):
    ArcadeError("DLLoader", message)
{}
