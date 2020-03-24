/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Text class wrapper
*/

#include "MySDL/Text.hpp"
#include "SDLError.hpp"

using namespace MySDL;

Text::Text(Font &font, const std::string &text, int ptsize, Window &window):
    _window(window), _font(font), _texture(nullptr), _characterSize(ptsize),
    _color({255, 255, 255, 255}), _text(text), _loadTexture(false)
{
    loadTexture();
}

Text::~Text()
{
    if (_texture)
        SDL_DestroyTexture(_texture);
}

SDL_Texture *Text::getTexture()
{
    if (_loadTexture)
        loadTexture();
    return (_texture);
}

void Text::loadTexture()
{
    SDL_Surface *surface = _font.renderText(_text, _characterSize, _color);
    SDL_Rect surfaceSize;

    if (!surface)
        throw arc::SDLError("Could not create text");
    if (_texture)
        SDL_DestroyTexture(_texture);
    _texture = SDL_CreateTextureFromSurface(_window.getRenderer(), surface);
    SDL_GetClipRect(surface, &surfaceSize);
    _rect.h = surfaceSize.h;
    _rect.w = surfaceSize.w;
    _size.x = _rect.w;
    _size.y = _rect.h;
    SDL_FreeSurface(surface);
    _loadTexture = false;
}

void Text::setPosition(const Vector &pos)
{
    _pos = pos;
    _rect.x = pos.x;
    _rect.y = pos.y;
}

void Text::setCharacterSize(int size)
{
    _characterSize = size;
    _loadTexture = true;
}

const Vector &Text::getPosition() const
{
    return (_pos);
}

const Vector &Text::getSize() const
{
    return (_size);
}

const SDL_Rect &Text::getRect() const
{
    return (_rect);
}

void Text::setColor(const SDL_Color &color)
{
    _color = color;
    _loadTexture = true;
}

const SDL_Color &Text::getColor() const
{
    return (_color);
}

void Text::setString(const std::string &str)
{
    _text = str;
    _loadTexture = true;
}
