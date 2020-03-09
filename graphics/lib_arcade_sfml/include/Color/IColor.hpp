/*
** EPITECH PROJECT, 2020
** Color
** File description:
** Color for MySf lib
*/

#ifndef ICOLOR_HPP_
#define ICOLOR_HPP_

#include <SFML/Graphics.hpp>

namespace MySf {

    namespace Color {

        class IColor {
        public:
            virtual ~IColor() = default;

            virtual IColor &operator=(const sf::Color &color) = 0;
            virtual IColor &operator=(const IColor &color) = 0;

            virtual void setColor(const sf::Color &color) = 0;
            virtual const sf::Color &getColor() = 0;
            virtual const sf::Color &getColor() const = 0;

            virtual void setColor(sf::Uint8 r, sf::Uint8 g,
                                  sf::Uint8 b, sf::Uint8 a) = 0;
        };

    }
}

#endif /* ICOLOR_HPP_ */
