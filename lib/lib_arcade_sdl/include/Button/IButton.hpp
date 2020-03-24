
/*
** EPITECH PROJECT, 2020
** IButton
** File description:
** Interface for buttons
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_

// #include <SFML/Graphics.hpp>
#include <SDL2/SDL.h>
#include "Color/IColor.hpp"
#include <functional>
#include "MySDL/Window.hpp"

namespace MySf {

    namespace Button {

        struct ButtonColor {
            ButtonColor() = delete;
            ButtonColor(const SDL_Color &_c, const SDL_Color &_h, const SDL_Color &_p, const SDL_Color &_inactif):
                c(_c), h(_h), p(_p), inactif(_inactif) {}

            ButtonColor(const SDL_Color &oneColor):
                c(oneColor), h(oneColor), p(oneColor), inactif(oneColor) {}

            SDL_Color c;
            SDL_Color h;
            SDL_Color p;
            SDL_Color inactif;
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
            virtual void setPosition(const MySDL::Vector &pos) = 0;
            virtual const MySDL::Vector &getPosition() const = 0;

            virtual void setSize(float x, float y) = 0;
            virtual void setSize(const MySDL::Vector &size) = 0;
            virtual const MySDL::Vector &getSize() const = 0;

            virtual const Color::IColor &getColor() const = 0;

            virtual void setLabel(const std::string &str) = 0;
            virtual const std::string &getLabel() const = 0;

            virtual void setFunc(const std::function<void ()> &func) = 0;

            virtual MySDL::Text &getText() = 0;

            virtual void setActivation(bool actif) = 0;
            virtual bool isActif() const = 0;

            virtual void setUpdateState(bool status) = 0;
            virtual bool getUpdateState() const = 0;

            virtual void update(const SDL_Event &event) = 0;

        protected:
            virtual void manageState() = 0;
            virtual void manageCurrentColor() = 0;
        };

    }

}

#endif /* IBUTTON_HPP_ */
