/*
** EPITECH PROJECT, 2020
** AColor
** File description:
** Abstract for colors
*/

#ifndef ACOLOR_HPP_
#define ACOLOR_HPP_

#include "Color/IColor.hpp"

namespace MySDL {

    namespace Color {

        class AColor: public IColor {
        public:
            AColor(const SDL_Color &color = {255, 0, 255, 255});
            virtual ~AColor() = default;

            virtual IColor &operator=(const SDL_Color &color);
            virtual IColor &operator=(const IColor &color);

            virtual void setColor(const SDL_Color &color) = 0;
            virtual const SDL_Color &getColor() = 0;

            virtual const SDL_Color &getColor() const;
            virtual void setColor(Uint8 r, Uint8 g,
                                  Uint8 b, Uint8 a);

        protected:
            SDL_Color _color;
        };

    }

}

#endif /* ACOLOR_HPP_ */
