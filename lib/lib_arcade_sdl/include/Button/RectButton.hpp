/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** RectButton
*/

#ifndef RECTBUTTON_HPP_
#define RECTBUTTON_HPP_

#include "Button/AButton.hpp"
#include "MySDL/Rectangle.hpp"

namespace MySf {

    namespace Button {

        class RectButton: public AButton {
        public:

            RectButton(MySDL::Window &w,
                       const MySDL::Vector &pos,
                       const MySDL::Vector &size,
                       MySDL::Font &f,
                       const ButtonColor &button,
                       const ButtonColor &text,
                       const std::string &label,
                       const std::function<void()> &fct);

            virtual void draw();

        protected:
            MySDL::Rectangle _rectangle;
        };

    }

}

#endif /* RECTBUTTON_HPP_ */
