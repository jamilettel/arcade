/*
** EPITECH PROJECT, 2020
** SmoothShifting
** File description:
** Color that shifts smoothly
*/

#ifndef SMOOTHSHIFTING_HPP_
#define SMOOTHSHIFTING_HPP_

#include "Color/AColor.hpp"

namespace MySDL {
    namespace Color {

        class SmoothShifting: public AColor {
        public:
            SmoothShifting(const SDL_Color &color = SDL_Color{255, 0, 255, 255},
                           Uint32 duration = 200);
            ~SmoothShifting() = default;

            void setColor(const SDL_Color &color);
            const SDL_Color &getColor();

        private:
            SDL_Color _target;
            SDL_Color _current;
            int _rDiff;
            int _gDiff;
            int _bDiff;
            int _aDiff;
            Uint32 _duration;
            Uint32 _finishTime;

        };

    }
}

#endif /* SMOOTHSHIFTING_HPP_ */
