/*
** EPITECH PROJECT, 2020
** AColor
** File description:
** cpp
*/

#include "Color/AColor.hpp"

using namespace MySDL::Color;

AColor::AColor(const SDL_Color &color):
    _color(color)
{}

const SDL_Color &AColor::getColor() const
{
    return (_color);
}


IColor &AColor::operator=(const SDL_Color &color)
{
    setColor(color);
    return (*this);
}

IColor &AColor::operator=(const IColor &color)
{
    setColor(color.getColor());
    return (*this);
}

void AColor::setColor(Uint8 r, Uint8 g,
                      Uint8 b, Uint8 a)
{
    setColor(SDL_Color{r, g, b, a});
}
