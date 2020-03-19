/*
** EPITECH PROJECT, 2020
** Utils
** File description:
** Color utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <SFML/Graphics.hpp>

namespace MySf {

    namespace Color {

        class Utils {
        public:
            static sf::Uint8 addToColor(sf::Uint8 color, int toAdd);
        };

    }

}

#endif /* UTILS_HPP_ */
