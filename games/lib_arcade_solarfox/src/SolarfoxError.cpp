/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Solarfox errors (exception class)
*/

#include "SolarfoxError.hpp"

using namespace arc;

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

SolarfoxError::SolarfoxError(const std::string &error): ArcadeError("Solarfox", error)
{}
