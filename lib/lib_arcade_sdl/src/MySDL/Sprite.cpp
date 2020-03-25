/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Sprite class wrapper
*/

#include "MySDL/Sprite.hpp"
#include "SDLError.hpp"

using namespace MySDL;

Sprite::Sprite(): _texture(nullptr), _rect{0, 0, 0, 0}, _rotation(0), _color{0, 0, 0, 0}
{}

Sprite::Sprite(const std::string &filepath, Window &window):
    _texture(nullptr), _rect{0, 0, 0, 0}, _rotation(0), _color{0, 0, 0, 0}
{
    loadFile(filepath, window);
}

void Sprite::loadFile(const std::string &filepath, Window &window)
{
    SDL_Surface *surface = IMG_Load(filepath.c_str());

    if (!surface)
        throw arc::SDLError("Could not load sprite '" + filepath + "'");
    _texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
    SDL_GetClipRect(surface, &_rect);
    _size.x = _rect.w;
    _size.y = _rect.h;
    SDL_FreeSurface(surface);
}

Sprite::~Sprite()
{
    if (_texture)
        SDL_DestroyTexture(_texture);
}

void Sprite::setPosition(const Vector &pos)
{
    _pos = pos;
    _rect.x = pos.x;
    _rect.y = pos.y;
}

void Sprite::setSize(const Vector &size)
{
    _size = size;
    _rect.w = size.x;
    _rect.h = size.y;
}

void Sprite::setRect(const SDL_Rect &rect)
{
    _rect = rect;
    _pos.x = _rect.x;
    _pos.y = _rect.y;
    _size.x = _rect.w;
    _size.y = _rect.h;
}

const Vector &Sprite::getPosition() const
{
    return (_pos);
}

const Vector &Sprite::getSize() const
{
    return (_size);
}

const SDL_Rect &Sprite::getRect() const
{
    return (_rect);
}

SDL_Texture *Sprite::getTexture()
{
    return (_texture);
}

void Sprite::setRotation(double rotation)
{
    _rotation = rotation;
}

double Sprite::getRotation() const
{
    return (_rotation);
}

const SDL_Color &Sprite::getColor() const
{
    return (_color);
}

void Sprite::setColor(const SDL_Color &color)
{
    _color = color;
}
