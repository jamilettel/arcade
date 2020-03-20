
/*
** EPITECH PROJECT, 2020
** IButton
** File description:
** Interface for buttons
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include "MySf/Color/IColor.hpp"
#include <functional>

namespace MySf {

    namespace Button {

        struct ButtonColor {
            ButtonColor() = delete;
            ButtonColor(const sf::Color &_c, const sf::Color &_h, const sf::Color &_p, const sf::Color &_inactif):
                c(_c), h(_h), p(_p), inactif(_inactif) {}

            ButtonColor(const sf::Color &oneColor):
                c(oneColor), h(oneColor), p(oneColor), inactif(oneColor) {}

            sf::Color c;
            sf::Color h;
            sf::Color p;
            sf::Color inactif;
        };

        enum ButtonState {
            NONE,
            HOVERING,
            PRESSED
        };

        class IButton {
        public:
            virtual ~IButton() = default;

            virtual void draw() = 0;

            virtual void setPosition(float x, float y) = 0;
            virtual void setPosition(const sf::Vector2f &pos) = 0;
            virtual const sf::Vector2f &getPosition() const = 0;

            virtual void setSize(float x, float y) = 0;
            virtual void setSize(const sf::Vector2f &size) = 0;
            virtual const sf::Vector2f &getSize() const = 0;

            virtual const Color::IColor &getColor() const = 0;

            virtual void setLabel(const std::string &str) = 0;
            virtual const std::string &getLabel() const = 0;

            virtual void setFunc(const std::function<void ()> &func) = 0;

            virtual sf::Text &getText() = 0;
            virtual void setButton(sf::Mouse::Button b) = 0;

            virtual void setActivation(bool actif) = 0;
            virtual bool isActif() const = 0;

            virtual void setUpdateState(bool status) = 0;
            virtual bool getUpdateState() const = 0;

        protected:
            virtual void manageState() = 0;
            virtual void manageCurrentColor() = 0;
        };

    }

}

#endif /* IBUTTON_HPP_ */
