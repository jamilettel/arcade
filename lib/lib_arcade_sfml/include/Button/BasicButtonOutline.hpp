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
                               sf::Vector2f pos,
                               sf::Vector2f size,
                               sf::Font &f,
                               const TriColor &button,
                               const TriColor &text,
                               const std::string &label,
                               const std::function<void()> &fct);

            virtual void draw();

        protected:
            sf::RectangleShape _lines;
        };

    }

}


#endif /* BASICBUTTONOUTLINE_HPP_ */
