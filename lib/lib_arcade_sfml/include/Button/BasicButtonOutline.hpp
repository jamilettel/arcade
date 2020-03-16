/*
** EPITECH PROJECT, 2020
** mysf
** File description:
** BasicButtonOutline
*/

#ifndef BASICBUTTONOUTLINE_HPP_
#define BASICBUTTONOUTLINE_HPP_

#include "Button/BasicButton.hpp"
#include "Color/SmoothShifting.hpp"
#include <iostream>

namespace MySf {

    namespace Button {

        class BasicButtonOutline: public BasicButton {
        public:

            BasicButtonOutline(sf::RenderWindow &w,
                               const sf::Vector2f &pos,
                               const sf::Vector2f &size,
                               sf::Font &f,
                               const ButtonColor &button,
                               const ButtonColor &text,
                               const std::string &label,
                               const std::function<void()> &fct);

            virtual void draw();

        protected:
            sf::RectangleShape _lines;
        };

    }

}


#endif /* BASICBUTTONOUTLINE_HPP_ */
