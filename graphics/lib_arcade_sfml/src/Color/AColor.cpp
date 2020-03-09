/*
** EPITECH PROJECT, 2020
** AColor
** File description:
** cpp
*/

#include "Color/AColor.hpp"

using namespace MySf::Color;

AColor::AColor(const sf::Color &color):
    _color(color)
{}

const sf::Color &AColor::getColor() const
{
    return (_color);
}


IColor &AColor::operator=(const sf::Color &color)
{
    setColor(color);
    return (*this);
}

IColor &AColor::operator=(const IColor &color)
{
    setColor(color.getColor());
    return (*this);
}

void AColor::setColor(sf::Uint8 r, sf::Uint8 g,
                      sf::Uint8 b, sf::Uint8 a)
{
    setColor(sf::Color(r, g, b, a));
}
