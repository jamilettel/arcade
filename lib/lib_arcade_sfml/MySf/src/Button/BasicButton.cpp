/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** BasicButton
*/

#include "MySf/Button/BasicButton.hpp"

using namespace MySf::Button;

BasicButton::BasicButton(sf::RenderWindow &w,
                         const sf::Vector2f &pos,
                         const sf::Vector2f &size,
                         sf::Font &f,
                         const ButtonColor &button,
                         const ButtonColor &text,
                         const std::string &label,
                         const std::function<void()> &fct):
    AButton(w, pos, size, f, button, text, fct)
{
    _buttonColor = std::unique_ptr<Color::IColor>(new Color::SmoothShifting(button.c, 300));
    _textColor = std::unique_ptr<Color::IColor>(new Color::SmoothShifting(text.c, 300));
    _label = label;
}

void BasicButton::draw()
{
    float radius = _size.y / 2.0f;
    sf::FloatRect textBounds = _t.getGlobalBounds();
    size_t size = _t.getCharacterSize();

    manageCurrentColor();
    _cs.setFillColor(_buttonColor->getColor());
    _rectangle.setFillColor(_buttonColor->getColor());

    _cs.setRadius(radius);
    _cs.setPosition(_pos);
    _window.draw(_cs);
    _cs.setPosition(_pos.x + _size.x - radius * 2, _pos.y);
    _window.draw(_cs);

    _rectangle.setPosition(_pos.x + radius, _pos.y);
    _rectangle.setSize(sf::Vector2f(_size.x - radius * 2, _size.y));
    _window.draw(_rectangle);

    _t.setString(_label);
    _t.setFont(_f);
    _t.setFillColor(_textColor->getColor());
    _t.setPosition(_pos.x + _size.x/2 - textBounds.width / 2,
                   _pos.y + _size.y/2 - size / 1.5f);
    _window.draw(_t);
}
