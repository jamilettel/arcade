/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** BasicButtonOutline
*/

#include "Button/BasicButtonOutline.hpp"

using namespace MySf::Button;

BasicButtonOutline::BasicButtonOutline(sf::RenderWindow &w,
                                       sf::Vector2f pos,
                                       sf::Vector2f size,
                                       sf::Font &f,
                                       const TriColor &button,
                                       const TriColor &text,
                                       const std::string &label,
                                       const std::function<void()> &fct):
    BasicButton(w, pos, size, f, button, text, label, fct)
{}

void BasicButtonOutline::draw()
{
    float radius = _size.y / 2.0f;

    BasicButton::draw();

    _cs.setOutlineThickness(3);
    _cs.setOutlineColor(_textColor->getColor());
    _lines.setFillColor(_textColor->getColor());

    _lines.setPosition(_pos.x + radius, _pos.y - 3);
    _lines.setSize(sf::Vector2f(_size.x - radius * 2, 3));
    _window.draw(_lines);
    _lines.setPosition(_pos.x + radius, _pos.y + _size.y);
    _lines.setSize(sf::Vector2f(_size.x - radius * 2, 3));
    _window.draw(_lines);
}
