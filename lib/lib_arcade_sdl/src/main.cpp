/*
** EPITECH PROJECT, 2020
** SDL tmp
** File description:
** sdl
*/

#include "MySDL/Window.hpp"
#include "MySDL/Sprite.hpp"
#include "MySDL/Text.hpp"
#include "MySDL/Rectangle.hpp"
#include "Button/RectButton.hpp"

#define BUTTON_COLOR MySDL::Button::ButtonColor(SDL_Color{0x0a, 0x0a, 0x0a, 0xff}, \
                                               SDL_Color{0x13, 0x13, 0x13, 0xff}, \
                                               SDL_Color{0x5f, 0x5f, 0x5f, 0xff}, \
                                               SDL_Color{0x34, 0x34, 0x34, 0xff})

#define TEXT_COLOR MySDL::Button::ButtonColor(SDL_Color{0xff, 0xff, 0xff, 0xff}, \
                                             SDL_Color{0xff, 0xff, 0xff, 0xff}, \
                                             SDL_Color{0xff, 0xff, 0xff, 0xff}, \
                                             SDL_Color{0x77, 0x77, 0x77, 0xff})

int main(void)
{
    MySDL::Window window(1600, 900, "SDL Test");
    MySDL::Sprite sprite("../../assets/nibbler/snake_head.png", window);
    MySDL::Font font("../../assets/font.ttf");
    MySDL::Text text(font, "Bonsoir BENJAMIN", 32, window);
    MySDL::Rectangle rect(SDL_Rect{200, 50, 260, 60}, SDL_Color{10, 10, 10, 255});

    MySDL::Button::RectButton button(window, MySDL::Vector(500, 500), MySDL::Vector(260, 50), font,
                                    BUTTON_COLOR, TEXT_COLOR, "OK Boomer", [] () {std::cout << "Bonsoir" << std::endl;});
    SDL_Event event;

    text.setPosition(MySDL::Vector(100, 100));
    text.setColor((SDL_Color){4, 100, 255, 255});
    sprite.setPosition(MySDL::Vector(500, 500));
    window.setFramerateLimit(60);
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return (0);
            button.update(event);
        }
        window.draw(sprite);
        window.draw(rect);
        window.draw(text);
        button.draw();
        window.display();
        window.clear(SDL_Color{28, 28, 28, 255});
    }
    return (0);
}

