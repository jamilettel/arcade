/*
** EPITECH PROJECT, 2020
** Color
** File description:
** Color utils
*/

#include "MySf/Color/Utils.hpp"

using namespace MySf::Color;

sf::Uint8 Utils::addToColor(sf::Uint8 color, int toAdd)
{
    int intColor = color;

    if (intColor + toAdd > 255)
        return (255);
    else if (intColor + toAdd < 0)
        return (0);
    return (color + static_cast<sf::Uint8>(toAdd));
}
