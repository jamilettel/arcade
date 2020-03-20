/*
** EPITECH PROJECT, 2020
** AButton
** File description:
** Abstract class for buttons
*/

#ifndef ABUTTON_HPP_
#define ABUTTON_HPP_

#include "MySf/Button/IButton.hpp"
#include <memory>
#include <iostream>

namespace MySf {

    namespace Button {

        class AButton: public IButton {
        public:
            AButton(sf::RenderWindow &w, sf::Vector2f pos, sf::Vector2f size, sf::Font &f,
                    const ButtonColor &button, const ButtonColor &text, const std::function<void()> &fct);

            virtual ~AButton() = default;

            virtual void draw() = 0;

            virtual void setPosition(float x, float y);
            virtual void setPosition(const sf::Vector2f &pos);
            virtual const sf::Vector2f &getPosition() const;
            virtual void setSize(float x, float y);
            virtual void setSize(const sf::Vector2f &size);
            virtual const sf::Vector2f &getSize() const;
            virtual const Color::IColor &getColor() const;
            virtual void setLabel(const std::string &str);
            virtual const std::string &getLabel() const;
            virtual void setFunc(const std::function<void ()> &func);
            virtual sf::Text &getText();
            virtual void setButton(sf::Mouse::Button b);

            virtual void setActivation(bool actif);
            virtual bool isActif() const;

            virtual void setUpdateState(bool status);
            virtual bool getUpdateState() const;

        protected:
            virtual void manageState();
            virtual void manageCurrentColor();

            sf::Mouse _mouse;
            sf::RenderWindow &_window;
            sf::Mouse::Button _button;
            sf::Vector2f _pos;
            sf::Vector2f _size;
            ButtonColor _bColor;
            sf::Color _bCurrentColor;
            sf::Color _tCurrentColor;
            ButtonColor _tColor;
            std::unique_ptr<Color::IColor> _buttonColor;
            std::unique_ptr<Color::IColor> _textColor;
            ButtonState _state;
            std::function<void()> _func;
            std::string _label;
            sf::Font &_f;
            sf::Text _t;
            bool _actif;
            bool _updateState;
        };

    }

}

#endif /* ABUTTON_HPP_ */
