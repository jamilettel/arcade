/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** RectButton
*/

#include "Button/RectButton.hpp"
#include "Color/SmoothShifting.hpp"

using namespace MySDL::Button;

RectButton::RectButton(MySDL::Window &w,
                       const MySDL::Vector &pos,
                       const MySDL::Vector &size,
                       MySDL::Font &f,
                       const ButtonColor &button,
                       const ButtonColor &text,
                       const std::string &label,
                       const std::function<void()> &fct):
    AButton(w, pos, size, f, button, text, fct), _rectangle(pos, size)
{
    _buttonColor = std::unique_ptr<Color::IColor>(new Color::SmoothShifting(button.c, 300));
    _textColor = std::unique_ptr<Color::IColor>(new Color::SmoothShifting(text.c, 300));
    _label = label;
}

void RectButton::draw()
{
    SDL_FRect textBounds = _t.getRect();
    size_t size = _t.getCharacterSize();
    MySDL::Vector wantedPosition(_pos.x + _size.x/2 - textBounds.w / 2,
                                 _pos.y + _size.y/2 - size / 2.5);

    manageCurrentColor();
    _rectangle.setColor(_buttonColor->getColor());
    _rectangle.setSize(_size);
    _rectangle.setPosition(_pos);
    _window.draw(_rectangle);
    _t.setString(_label);
    _t.setColor(_textColor->getColor());
    _t.setPosition(wantedPosition);
    _window.draw(_t);
}
