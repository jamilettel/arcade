/*
** EPITECH PROJECT, 2020
** MySF
** File description:
** BasicButton
*/

#ifndef BASICBUTTON_HPP_
#define BASICBUTTON_HPP_

#include "Button/AButton.hpp"
#include "Color/SmoothShifting.hpp"
#include <iostream>

namespace MySf {

    namespace Button {

        class BasicButton: public AButton {
        public:

            BasicButton(sf::RenderWindow &w,
                        sf::Vector2f pos,
                        sf::Vector2f size,
                        sf::Font &f,
                        const TriColor &button,
                        const TriColor &text,
                        const std::string &label,
                        const std::function<void()> &fct);

            virtual void draw();

        protected:
            sf::RectangleShape _rectangle;
            sf::CircleShape _cs;
        };

    }

}

#endif /* BASICBUTTON_HPP_ */