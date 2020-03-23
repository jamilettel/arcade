/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Window class wrapper
*/

#include "MySDL/Window.hpp"
#include "SDLError.hpp"
#include "MySDL/Sprite.hpp"

using namespace MySDL;

Vector::Vector(): x(0), y(0)
{}

Vector::Vector(int _x, int _y): x(_x), y(_y)
{}

Window::Window(int width, int height): _window(nullptr), _renderer(nullptr),
                                       _currentFrameTime(0)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw arc::SDLError("Could not initialize library");
    if (SDL_CreateWindowAndRenderer(width, height, 0, &_window, &_renderer))
        throw arc::SDLError("Could not create window and renderer");
}

Window::~Window()
{
    if (_window && _renderer) {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
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

void Window::draw(Sprite &sprite)
{
    SDL_Rect dest = sprite.getRect();

    SDL_RenderCopy(_renderer, sprite.getTexture(), NULL, &dest);
}

void Window::setFramerateLimit(int limit)
{
    if (!limit)
        _desiredFrameTime = 0;
    else
        _desiredFrameTime = 1000 / limit;
}
