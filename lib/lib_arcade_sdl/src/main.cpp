/*
** EPITECH PROJECT, 2020
** SDL tmp
** File description:
** sdl
*/

#include "MySDL/Window.hpp"
#include "MySDL/Sprite.hpp"
#include "MySDL/Text.hpp"

int main(void)
{
    MySDL::Window window(1600, 900, "SDL Test");
    MySDL::Sprite sprite("../../assets/nibbler/snake_head.png", window);
    MySDL::Font font("../../assets/font.ttf");
    MySDL::Text text(font, "Bonsoir BENJAMIN", 32, window);
    SDL_Event event;

    text.setPosition(MySDL::Vector(100, 100));
    text.setColor((SDL_Color){4, 100, 255, 255});
    sprite.setPosition(MySDL::Vector(500, 500));
    window.setFramerateLimit(60);
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return (0);
        }
        window.draw(sprite);
        window.draw(text);
        window.display();
        window.clear();
    }
    return (0);
}

