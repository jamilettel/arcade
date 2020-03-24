/*
** EPITECH PROJECT, 2020
** MySDL
** File description:
** AButton
*/

#include "Button/AButton.hpp"

using namespace MySDL::Button;

AButton::AButton(MySDL::Window &w, MySDL::Vector pos, MySDL::Vector size,
                 MySDL::Font &f, const ButtonColor &button,
                 const ButtonColor &text, const std::function<void()> &fct):
    _window(w), _pos(pos), _size(size), _bColor(button), _tColor(text), _state(NONE),
    _func(fct), _f(f), _t(f, "Button", 32, _window), _actif(true), _updateState(true),
    _buttonPressed(false)
{}

void AButton::setPosition(float x, float y)
{
    setPosition(MySDL::Vector(x, y));
}

void AButton::setPosition(const MySDL::Vector &pos)
{
    _pos = pos;
}

const MySDL::Vector &AButton::getPosition() const
{
    return (_size);
}

void AButton::setSize(float x, float y)
{
    setSize(MySDL::Vector(x, y));
}

void AButton::setSize(const MySDL::Vector &size)
{
    _size = size;
}

const MySDL::Vector &AButton::getSize() const
{
    return (_size);
}

const MySDL::Color::IColor &AButton::getColor() const
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

MySDL::Text &AButton::getText()
{
    return (_t);
}

void AButton::manageState()
{
    MySDL::Vector pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    bool hovering = false;

    if (!_updateState) {
        _state = NONE;
        return;
    }
    if (pos.x >= _pos.x && pos.x < _pos.x + _size.x &&
        pos.y >= _pos.y && pos.y < _pos.y + _size.y)
        hovering = true;
    if (_state != PRESSED) {
        if (_buttonPressed && _state == HOVERING) {
            _state = PRESSED;
            return;
        }
    } else if (!_buttonPressed) {
        _state = PRESSED;
        if (hovering && _func)
            _func();
    } else
        return;
    if (hovering && !_buttonPressed) {
        _state = HOVERING;
        return;
    }
    _state = NONE;
}

void AButton::manageCurrentColor()
{
    SDL_Color cButton;
    SDL_Color cText;

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

void AButton::setUpdateState(bool status)
{
    _updateState = status;
}

bool AButton::getUpdateState() const
{
    return (_updateState);
}

void AButton::update(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        _buttonPressed = true;
    else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
        _buttonPressed = false;
}
