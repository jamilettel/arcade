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
#include <SDL2/SDL_ttf.h>
#include <string>

namespace MySDL {

    class Rectangle;
    class Sprite;
    class Text;

    struct Vector {
        Vector();
        Vector(int, int);

        int x;
        int y;
    };

    class Window {
    public:
        Window(int width, int height, const std::string &title = "SDL Window",
               Uint32 windiwFlags = 0, Uint32 rendererFlags = 0);
        ~Window();

        void setFramerateLimit(int limit);
        void clear(SDL_Color color = {0, 0, 0, 255});

        void draw(Sprite &sprite);
        void draw(Text &font);
        // void draw(const Rectangle &rect);

        void display();

        SDL_Renderer *getRenderer();

    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;

        int _desiredFrameTime;
        size_t _currentFrameTime;

    };

}

#endif /* SDL_WINDOW_HPP_ */