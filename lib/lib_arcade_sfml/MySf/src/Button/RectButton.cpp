/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** RectButton
*/

#include "MySf/Button/RectButton.hpp"
#include "MySf/Color/SmoothShifting.hpp"

using namespace MySf::Button;

RectButton::RectButton(sf::RenderWindow &w,
                       const sf::Vector2f &pos,
                       const sf::Vector2f &size,
                       sf::Font &f,
                       const ButtonColor &button,
                       const ButtonColor &text,
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
    sf::Vector2f wantedPosition(_pos.x + _size.x/2 - textBounds.width / 2,
                                _pos.y + _size.y/2 - size / 2.5);

    manageCurrentColor();
    _rectangle.setFillColor(_buttonColor->getColor());
    _rectangle.setSize(_size);
    _rectangle.setPosition(_pos);
    _window.draw(_rectangle);
    _t.setString(_label);
    _t.setFont(_f);
    _t.setFillColor(_textColor->getColor());
    _t.move(wantedPosition.x - textBounds.left, wantedPosition.y - textBounds.top);
    _window.draw(_t);
}
