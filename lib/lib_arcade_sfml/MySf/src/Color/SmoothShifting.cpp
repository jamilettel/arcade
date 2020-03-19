/*
** EPITECH PROJECT, 2020
** SmoothShifting
** File description:
** color that shifts smoothly
*/

#include "MySf/Color/SmoothShifting.hpp"
#include "MySf/Color/Utils.hpp"
#include <cmath>
#include <iostream>

using namespace MySf::Color;

sf::Clock SmoothShifting::_clock;

SmoothShifting::SmoothShifting(const sf::Color &color, sf::Int32 duration):
    AColor(color), _target(color), _current(color),
    _duration(duration), _finishTime(0)
{}

void SmoothShifting::setColor(const sf::Color &color)
{
    _target = color;
    _color = _current;
    _rDiff = _color.r - _target.r;
    _gDiff = _color.g - _target.g;
    _bDiff = _color.b - _target.b;
    _aDiff = _color.a - _target.a;
    _finishTime = _clock.getElapsedTime().asMilliseconds() + _duration;
}

const sf::Color &SmoothShifting::getColor()
{
    sf::Int32 current = _clock.getElapsedTime().asMilliseconds();
    double percentage = 0;

    if (_finishTime > current) {
        percentage = static_cast<double>(_finishTime - current) /
            static_cast<double>(_duration);
        percentage *= -1;
        percentage = percentage * percentage * percentage + 1;
        percentage = 1 - percentage;
        _current.r = Utils::addToColor(_target.r, _rDiff * percentage);
        _current.g = Utils::addToColor(_target.g, _gDiff * percentage);
        _current.b = Utils::addToColor(_target.b, _bDiff * percentage);
        _current.a = Utils::addToColor(_target.a, _aDiff * percentage);
    } else {
        _color = _target;
        _current = _color;
    }
    return (_current);
}
