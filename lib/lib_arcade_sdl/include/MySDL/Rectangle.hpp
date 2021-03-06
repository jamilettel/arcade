/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Rectangle class wrapper
*/

#ifndef MYSDL_RECTANGLE_HPP_
#define MYSDL_RECTANGLE_HPP_

#include "MySDL/Window.hpp"

namespace MySDL {

    class Rectangle {
    public:
        Rectangle(const Vector &pos, const Vector &size,
                  const SDL_Color &color = {255, 255, 255, 255});
        Rectangle(const SDL_FRect &rect,
                  const SDL_Color &color = {255, 255, 255, 255});

        ~Rectangle() = default;

        Rectangle(const Rectangle &rhs) = delete;
        Rectangle &operator=(const Rectangle &rhs) = delete;

        void setPosition(const Vector &pos);
        void setSize(const Vector &size);
        void setRect(const SDL_FRect &rect);
        void setColor(const SDL_Color &color);

        const Vector &getPosition() const;
        const Vector &getSize() const;
        const SDL_FRect &getRect() const;
        const SDL_Color &getColor() const;

        void setOutlineThickness(int thicc);
        int getOutlineThickness() const;

        void setOutlineColor(const SDL_Color &color);
        const SDL_Color &getOutlineColor() const;

    private:
        Vector _pos;
        Vector _size;
        SDL_FRect _rect;

        SDL_Color _color;

        int _outlineThickness;
        SDL_Color _outlineColor;
    };

}

#endif /* MYSDL_RECTANGLE_HPP_ */
