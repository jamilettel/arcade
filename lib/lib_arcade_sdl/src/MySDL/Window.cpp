/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Window class wrapper
*/

#include "MySDL/Window.hpp"
#include "SDLError.hpp"
#include "MySDL/Sprite.hpp"
#include "MySDL/Text.hpp"
#include "MySDL/Rectangle.hpp"

using namespace MySDL;

Vector::Vector(): x(0), y(0)
{}

Vector::Vector(int _x, int _y): x(_x), y(_y)
{}

Window::Window(int width, int height, const std::string &title,
               Uint32 windowFlags, Uint32 rendererFlags):
    _window(nullptr), _renderer(nullptr), _currentFrameTime(0)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)<0 || IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG || TTF_Init()<0)
        throw arc::SDLError("Could not initialize library");
    _window = SDL_CreateWindow(title.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width, height, windowFlags);
    _renderer = SDL_CreateRenderer(_window, 0, rendererFlags);
    if (!_window || !_renderer)
        throw arc::SDLError("Could not create window and renderer");
}

Window::~Window()
{
    if (_window && _renderer) {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
    }
}

void Window::display()
{
    int frameTime = SDL_GetTicks() - _currentFrameTime;

    if (frameTime < _desiredFrameTime)
        SDL_Delay(_desiredFrameTime - frameTime);
    SDL_RenderPresent(_renderer);
    _currentFrameTime = SDL_GetTicks();
}

void Window::clear(SDL_Color color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(_renderer);
}

void Window::draw(const Rectangle &rect)
{
    SDL_Color color = rect.getColor();

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &rect.getRect());
}

void Window::draw(Sprite &sprite)
{
    SDL_Rect dest = sprite.getRect();

    SDL_RenderCopy(_renderer, sprite.getTexture(), NULL, &dest);
}

void Window::draw(Text &Text)
{
    SDL_Rect dest = Text.getRect();

    SDL_RenderCopy(_renderer, Text.getTexture(), NULL, &dest);
}

void Window::setFramerateLimit(int limit)
{
    if (!limit)
        _desiredFrameTime = 0;
    else
        _desiredFrameTime = 1000 / limit;
}

SDL_Renderer* Window::getRenderer()
{
    return (_renderer);
}

bool operator==(const SDL_Color &lhs, const SDL_Color &rhs)
{
    return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.b);
}

bool operator!=(const SDL_Color &lhs, const SDL_Color &rhs)
{
    return !(lhs == rhs);
}
