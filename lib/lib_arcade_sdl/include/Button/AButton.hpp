/*
** EPITECH PROJECT, 2020
** AButton
** File description:
** Abstract class for buttons
*/

#ifndef ABUTTON_HPP_
#define ABUTTON_HPP_

#include "Button/IButton.hpp"
#include "MySDL/Text.hpp"
#include <memory>
#include <iostream>

namespace MySf {

    namespace Button {

        class AButton: public IButton {
        public:
            AButton(MySDL::Window &w, MySDL::Vector pos, MySDL::Vector size, MySDL::Font &f,
                    const ButtonColor &button, const ButtonColor &text, const std::function<void()> &fct);

            virtual ~AButton() = default;

            // virtual void draw() = 0;

            virtual void setPosition(float x, float y) override;
            virtual void setPosition(const MySDL::Vector &pos) override;
            virtual const MySDL::Vector &getPosition() const override;
            virtual void setSize(float x, float y) override;
            virtual void setSize(const MySDL::Vector &size) override;
            virtual const MySDL::Vector &getSize() const override;
            virtual const Color::IColor &getColor() const override;
            virtual void setLabel(const std::string &str) override;
            virtual const std::string &getLabel() const override;
            virtual void setFunc(const std::function<void ()> &func) override;
            virtual MySDL::Text &getText() override;

            virtual void setActivation(bool actif) override;
            virtual bool isActif() const override;

            virtual void setUpdateState(bool status) override;
            virtual bool getUpdateState() const override;

            virtual void update(const SDL_Event &event) override;

        protected:
            virtual void manageState() override;
            virtual void manageCurrentColor() override;

            MySDL::Window &_window;
            MySDL::Vector _pos;
            MySDL::Vector _size;
            ButtonColor _bColor;
            SDL_Color _bCurrentColor;
            SDL_Color _tCurrentColor;
            ButtonColor _tColor;
            std::unique_ptr<Color::IColor> _buttonColor;
            std::unique_ptr<Color::IColor> _textColor;
            ButtonState _state;
            std::function<void()> _func;
            std::string _label;
            MySDL::Font &_f;
            MySDL::Text _t;
            bool _actif;
            bool _updateState;

            bool _buttonPressed;
        };

    }

}

#endif /* ABUTTON_HPP_ */
