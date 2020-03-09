/*
** EPITECH PROJECT, 2020
** SmoothShifting
** File description:
** Color that shifts smoothly
*/

#ifndef SMOOTHSHIFTING_HPP_
#define SMOOTHSHIFTING_HPP_

#include "Color/AColor.hpp"

namespace MySf {
    namespace Color {

        class SmoothShifting: public AColor {
        public:
            SmoothShifting(const sf::Color &color = sf::Color::Magenta,
                           sf::Int32 duration = 200);
            ~SmoothShifting() = default;

            void setColor(const sf::Color &color);
            const sf::Color &getColor();

        private:
            static sf::Clock _clock;

            sf::Color _target;
            sf::Color _current;
            int _rDiff;
            int _gDiff;
            int _bDiff;
            int _aDiff;
            sf::Int32 _duration;
            sf::Int32 _finishTime;
        };

    }
}

#endif /* SMOOTHSHIFTING_HPP_ */
