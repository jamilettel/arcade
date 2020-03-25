/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Font class wrapper
*/

#include "MySDL/Font.hpp"
#include "SDLError.hpp"
#include <algorithm>

using namespace MySDL;

int Font::_instances = 0;

Font::Font(const std::string &filepath, int ptsize): _style(0), _filepath(filepath)
{
    if (!_instances) {
        if (TTF_Init() < 0)
            throw arc::SDLError("Could not int fonts");
    }
    _instances++;
    loadFont(ptsize);
}

Font::~Font()
{
    std::for_each(_fonts.begin(), _fonts.end(),
                  [] (const std::pair<int, TTF_Font *> &pair) {
                      if (pair.second)
                          TTF_CloseFont(pair.second);
                  });
    _instances--;
    if (!_instances)
        TTF_Quit();
}

TTF_Font *Font::getFont(int ptsize)
{
    if (!_fonts.count(ptsize))
        loadFont(ptsize);
    return (_fonts[ptsize]);
}

void Font::loadFont(int ptsize)
{
    _fonts[ptsize] = TTF_OpenFont(_filepath.c_str(), ptsize);

    if (!_fonts[ptsize])
        throw arc::SDLError("Could not load font '" + _filepath + "'");
}

SDL_Surface *Font::renderText(const std::string &string, int ptsize, const SDL_Color &color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(getFont(ptsize), string.c_str(), color);

    if (!surface)
        throw arc::SDLError("Could not render text");
    return (surface);
}

void Font::setStyle(int fontStyle)
{
    _style = fontStyle;
    std::for_each(_fonts.begin(), _fonts.end(),
                  [&fontStyle] (const std::pair<int, TTF_Font *> &pair) {
                      if (pair.second)
                          TTF_SetFontStyle(pair.second, fontStyle);
                  });
}
