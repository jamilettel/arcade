/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** AButton
*/

#include "Button/AButton.hpp"

using namespace MySf::Button;

AButton::AButton(sf::RenderWindow &w, sf::Vector2f pos, sf::Vector2f size, sf::Font &f,
                 const ButtonColor &button, const ButtonColor &text, const std::function<void()> &fct):
    _window(w), _button(sf::Mouse::Button::Left), _pos(pos),
    _size(size), _bColor(button), _tColor(text), _state(NONE),
    _func(fct), _f(f), _actif(true) {}

void AButton::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void AButton::setPosition(const sf::Vector2f &pos)
{
    _pos = pos;
}

const sf::Vector2f &AButton::getPosition() const
{
    return (_size);
}

void AButton::setSize(float x, float y)
{
    setSize(sf::Vector2f(x, y));
}

void AButton::setSize(const sf::Vector2f &size)
{
    _size = size;
}

const sf::Vector2f &AButton::getSize() const
{
    return (_size);
}

const MySf::Color::IColor &AButton::getColor() const
{
    return (*_buttonColor.get());
}

void AButton::setLabel(const std::string &str)
{
    _label = str;
}

const std::string &AButton::getLabel() const
{
    return (_label);
}

void AButton::setFunc(const std::function<void ()> &func)
{
    _func = func;
}

sf::Text &AButton::getText()
{
    return (_t);
}

void AButton::setButton(sf::Mouse::Button b)
{
    _button = b;
}

void AButton::manageState()
{
    sf::Vector2i pos = _mouse.getPosition(_window);
    bool hovering = false;

    if (pos.x >= _pos.x && pos.x < _pos.x + _size.x &&
        pos.y >= _pos.y && pos.y < _pos.y + _size.y)
        hovering = true;
    if (_state != PRESSED) {
        if (_mouse.isButtonPressed(_button) && _state == HOVERING) {
            _state = PRESSED;
            return;
        }
    } else if (!_mouse.isButtonPressed(_button)) {
        _state = PRESSED;
        if (hovering && _func)
            _func();
    } else
        return;
    if (hovering && !_mouse.isButtonPressed(_button)) {
        _state = HOVERING;
        return;
    }
    _state = NONE;
}

void AButton::manageCurrentColor()
{
    sf::Color cButton;
    sf::Color cText;

    if (_actif) {
        manageState();
        switch (_state) {
        case (NONE):
            cButton = _bColor.c;
            cText = _tColor.c;
            break;
        case (PRESSED):
            cButton = _bColor.p;
            cText = _tColor.p;
            break;
        case (HOVERING):
            cButton = _bColor.h;
            cText = _tColor.h;
            break;
        }
    } else {
        cButton = _bColor.inactif;
        cText = _tColor.inactif;
    }
    if (_bCurrentColor != cButton) {
        _bCurrentColor = cButton;
        _buttonColor->setColor(cButton);
    }
    if (_tCurrentColor != cText) {
        _tCurrentColor = cText;
        _textColor->setColor(cText);
    }
}

void AButton::setActivation(bool actif)
{
    _actif = actif;
}

bool AButton::isActif() const
{
    return (_actif);
}
