/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Rectangle class wrapper
*/

#include "MySDL/Rectangle.hpp"

using namespace MySDL;

Rectangle::Rectangle(const Vector &pos, const Vector &size, const SDL_Color &color):
    _pos(pos), _size(size), _color(color)
{
    _rect.x = _pos.x;
    _rect.y = _pos.y;
    _rect.w = _size.x;
    _rect.h = _size.y;
}

Rectangle::Rectangle(const SDL_Rect &rect, const SDL_Color &color):
    _rect(rect), _color(color)
{
    _pos.x = _rect.x;
    _pos.y = _rect.y;
    _size.x = _rect.w;
    _size.y = _rect.h;
}
void Rectangle::setPosition(const Vector &pos)
{
    _pos = pos;
    _rect.x = pos.x;
    _rect.y = pos.y;
}

void Rectangle::setSize(const Vector &size)
{
    _size = size;
    _rect.w = size.x;
    _rect.h = size.y;
}

void Rectangle::setRect(const SDL_Rect &rect)
{
    _rect = rect;
    _pos.x = _rect.x;
    _pos.y = _rect.y;
    _size.x = _rect.w;
    _size.y = _rect.h;
}

const Vector &Rectangle::getPosition() const
{
    return (_pos);
}

const Vector &Rectangle::getSize() const
{
    return (_size);
}

const SDL_Rect &Rectangle::getRect() const
{
    return (_rect);
}

const SDL_Color &Rectangle::getColor() const
{
    return (_color);
}

void Rectangle::setColor(const SDL_Color &color)
{
    _color = color;
}
