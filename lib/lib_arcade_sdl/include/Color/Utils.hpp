/*
** EPITECH PROJECT, 2020
** Utils
** File description:
** Color utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "Color/IColor.hpp"

namespace MySDL {

    namespace Color {

        class Utils {
        public:
            static Uint8 addToColor(Uint8 color, int toAdd);
        };

    }

}

#endif /* UTILS_HPP_ */
