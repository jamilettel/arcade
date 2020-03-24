/*
** EPITECH PROJECT, 2020
** Color
** File description:
** Color for MySf lib
*/

#ifndef ICOLOR_HPP_
#define ICOLOR_HPP_

// #include <SFML/Graphics.hpp>
#include <SDL2/SDL.h>

namespace MySf {

    namespace Color {

        class IColor {
        public:
            virtual ~IColor() = default;

            virtual IColor &operator=(const SDL_Color &color) = 0;
            virtual IColor &operator=(const IColor &color) = 0;

            virtual void setColor(const SDL_Color &color) = 0;
            virtual const SDL_Color &getColor() = 0;
            virtual const SDL_Color &getColor() const = 0;

            virtual void setColor(Uint8 r, Uint8 g,
                                  Uint8 b, Uint8 a) = 0;
        };

    }
}

#endif /* ICOLOR_HPP_ */
