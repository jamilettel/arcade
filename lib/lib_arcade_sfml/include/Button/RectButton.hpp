/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** RectButton
*/

#ifndef RECTBUTTON_HPP_
#define RECTBUTTON_HPP_

#include "Button/AButton.hpp"

namespace MySf {

    namespace Button {

        class RectButton: public AButton {
        public:

            RectButton(sf::RenderWindow &w,
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
        };

    }

}

#endif /* RECTBUTTON_HPP_ */
