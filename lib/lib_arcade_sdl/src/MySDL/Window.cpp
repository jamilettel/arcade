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

bool Vector::operator==(const Vector &lhs) const
{
    return (x == lhs.x && y == lhs.y);
}

bool Vector::operator!=(const Vector &lhs) const
{
    return !(*this == lhs);
}

Window::Window(int width, int height, const std::string &title,
               Uint32 windowFlags, Uint32):
    _window(nullptr), _renderer(nullptr), _currentFrameTime(0), _open(true)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)<0 || IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG)
        throw arc::SDLError("Could not initialize library");
    // _window = SDL_CreateWindow(title.c_str(),
    //                            SDL_WINDOWPOS_UNDEFINED,
    //                            SDL_WINDOWPOS_UNDEFINED,
    //                            width, height, windowFlags);
    // _renderer = SDL_CreateRenderer(_window, 0, rendererFlags);
    SDL_CreateWindowAndRenderer(width, height, windowFlags, &_window, &_renderer);
    if (!_window || !_renderer)
        throw arc::SDLError("Could not create window and renderer");
    SDL_SetWindowTitle(_window, title.c_str());
}

Window::~Window()
{
    if (_window && _renderer) {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        IMG_Quit();
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

void Window::draw(const Rectangle &rect)
{
    SDL_Color color = rect.getColor();
    int thickness = rect.getOutlineThickness();

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &rect.getRect());

    while (thickness) {
        SDL_Rect outline = rect.getRect();

        outline.x -= thickness;
        outline.y -= thickness;
        outline.w += 2 * thickness;
        outline.h += 2 * thickness;
        color = rect.getOutlineColor();
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(_renderer, &outline);

        if (thickness > 0)
            thickness--;
        else
            thickness++;
    }
}

void Window::draw(Sprite &sprite)
{
    SDL_Rect dest = sprite.getRect();

    if (sprite.getTexture())
        SDL_RenderCopyEx(_renderer, sprite.getTexture(), NULL, &dest,
                         sprite.getRotation(), NULL, SDL_FLIP_NONE);
}

void Window::draw(Text &text)
{
    SDL_Rect dest = text.getRect();

    if (text.getTexture())
        SDL_RenderCopyEx(_renderer, text.getTexture(), NULL, &dest,
                         text.getRotation(), NULL, SDL_FLIP_NONE);
}

void Window::setFramerateLimit(int limit)
{
    if (!limit)
        _desiredFrameTime = 0;
    else
        _desiredFrameTime = 1000 / limit;
}

void Window::close()
{
    _open = false;
}

bool Window::isOpen() const
{
    return (_open);
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
