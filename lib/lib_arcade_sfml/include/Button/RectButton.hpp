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
                       const sf::Vector2f &pos,
                       const sf::Vector2f &size,
                       sf::Font &f,
                       const ButtonColor &button,
                       const ButtonColor &text,
                       const std::string &label,
                       const std::function<void()> &fct);

            virtual void draw();

        protected:
            sf::RectangleShape _rectangle;
        };

    }

}

#endif /* RECTBUTTON_HPP_ */
