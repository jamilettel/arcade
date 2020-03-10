/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** RectButton
*/

#include "Button/RectButton.hpp"
#include "Color/SmoothShifting.hpp"

using namespace MySf::Button;

RectButton::RectButton(sf::RenderWindow &w,
                       sf::Vector2f pos,
                       sf::Vector2f size,
                       sf::Font &f,
                       const TriColor &button,
                       const TriColor &text,
                       const std::string &label,
                       const std::function<void()> &fct):
    AButton(w, pos, size, f, button, text, fct)
{
    _buttonColor = std::unique_ptr<Color::IColor>(new Color::SmoothShifting(button.c, 150));
    _textColor = std::unique_ptr<Color::IColor>(new Color::SmoothShifting(text.c, 150));
    _label = label;
}

void RectButton::draw()
{
    sf::FloatRect textBounds = _t.getGlobalBounds();
    size_t size = _t.getCharacterSize();

    manageCurrentColor();
    _rectangle.setFillColor(_buttonColor->getColor());
    _rectangle.setSize(_size);
    _rectangle.setPosition(_pos);
    _window.draw(_rectangle);
    _t.setString(_label);
    _t.setFont(_f);
    _t.setFillColor(_textColor->getColor());
    _t.setPosition(_pos.x + _size.x/2 - textBounds.width / 2,
                   _pos.y + _size.y/2 - size / 1.5f);
    _window.draw(_t);
}
