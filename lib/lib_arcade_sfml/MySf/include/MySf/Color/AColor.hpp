/*
** EPITECH PROJECT, 2020
** AColor
** File description:
** Abstract for colors
*/

#ifndef ACOLOR_HPP_
#define ACOLOR_HPP_

#include "MySf/Color/IColor.hpp"

namespace MySf {

    namespace Color {

        class AColor: public IColor {
        public:
            AColor(const sf::Color &color = sf::Color::Magenta);
            virtual ~AColor() = default;

            virtual IColor &operator=(const sf::Color &color);
            virtual IColor &operator=(const IColor &color);

            virtual void setColor(const sf::Color &color) = 0;
            virtual const sf::Color &getColor() = 0;

            virtual const sf::Color &getColor() const;
            virtual void setColor(sf::Uint8 r, sf::Uint8 g,
                                  sf::Uint8 b, sf::Uint8 a);

        protected:
            sf::Color _color;
        };

    }

}

#endif /* ACOLOR_HPP_ */
