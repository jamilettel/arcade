/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Window class wrapper
*/

#ifndef SDL_WINDOW_HPP_
#define SDL_WINDOW_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

namespace MySDL {

    class Rectangle;
    class Sprite;

    struct Vector {
        Vector();
        Vector(int, int);

        int x;
        int y;
    };

    class Window {
    public:
        Window(int width, int height);
        ~Window();

        void setFramerateLimit(int limit);
        void clear(SDL_Color color = {0, 0, 0, 255});

        void draw(Sprite &sprite);
        void draw(const Rectangle &rect);

        void display();

    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;

        int _desiredFrameTime;
        size_t _currentFrameTime;

    };

}

#endif /* SDL_WINDOW_HPP_ */
