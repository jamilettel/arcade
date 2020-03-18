/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** InputZone
*/

#include "InputZone.hpp"

using namespace MySf;

InputZone::InputZone(sf::RenderWindow &window,
                     const sf::Vector2f &pos,
                     const sf::Vector2f &size,
                     sf::Font &font,
                     const std::string &placeHolder):
    _placeHolder(placeHolder), _font(font), _cursorPos(0), _hasFocus(false),
    _window(window), _pos(pos), _size(size), _colorText(sf::Color(0x0a0a0aff)),
    _colorBackground(sf::Color(0xefefefff)), _colorOutline(sf::Color(0x1c1c1cff)),
    _colorPlaceHolder(sf::Color(0xaaaaaaff)), _focusOutline(0x0a5eeeff), _unfocusedOutline(0x3c3c3cff),
    _isFull(false)
{
    applySizeAndPos();
    _text.setFont(_font);
}

void InputZone::applySizeAndPos()
{
    int textSize = _text.getCharacterSize();

    _rs.setPosition(_pos);
    _rs.setSize(_size);
    _rs.setOutlineThickness(3);
    _text.setPosition(_pos.x + 5, _pos.y + (_size.y / 2 - textSize / 1.5));
    _cursor.setSize(sf::Vector2f(3, textSize + 5));
}

void InputZone::setPosition(sf::Vector2f pos)
{
    _pos = pos;
    applySizeAndPos();
}

const sf::Vector2f &InputZone::getPosition() const
{
    return (_pos);
}

void InputZone::setSize(sf::Vector2f size)
{
    _size = size;
    applySizeAndPos();
}

const sf::Vector2f &InputZone::getSize() const
{
    return (_size);
}

void InputZone::setPlaceHolder(const std::string &placeHolder)
{
    _placeHolder = placeHolder;
}

const sf::String &InputZone::getPlaceHolder() const
{
    return (_placeHolder);
}

void InputZone::setFont(const sf::Font &font)
{
    _font = font;
}

const sf::Font &InputZone::getFont() const
{
    return (_font);
}

const sf::String &InputZone::getInput() const
{
    return (_content);
}



void InputZone::setTextColor(const sf::Color &color)
{
    _colorText.setColor(color);
}

void InputZone::setBackgroundColor(const sf::Color &color)
{
    _colorBackground.setColor(color);
}

void InputZone::setPlaceHolderColor(const sf::Color &color)
{
    _colorPlaceHolder.setColor(color);
}

void InputZone::setOutlineColor(const sf::Color &focused, const sf::Color &unfocused)
{
    _focusOutline = focused;
    _unfocusedOutline = unfocused;
}

void InputZone::addChar(sf::Uint32 c)
{
    if (!_isFull) {
        _content.insert(_cursorPos, c);
        _cursorPos++;
        _clock.restart();
    }
}

void InputZone::removeChar()
{
    if (_content.getSize() && _cursorPos) {
        _content.erase(_cursorPos - 1);
        _cursorPos--;
        _clock.restart();
    }
}

void InputZone::update(const sf::Event &event)
{
    if (!_hasFocus)
        return;
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') {
            removeChar();
        } else if (event.text.unicode == 127) {
            _cursorPos++;
            removeChar();
        } else if (event.text.unicode == '\r' || event.text.unicode == '\t') {
            _hasFocus = false;
        } else {
            addChar(event.text.unicode);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left && _cursorPos > 0) {
            _cursorPos--;
            _clock.restart();
        } else if (event.key.code == sf::Keyboard::Right) {
            _cursorPos++;
            _clock.restart();
        }
        if (_cursorPos > _content.getSize()) {
            _cursorPos = _content.getSize();
        }
    }
}

void InputZone::draw()
{
    sf::FloatRect globalBounds = _rs.getGlobalBounds();
    sf::Vector2i mousePos = _mouse.getPosition(_window);

    if (_mouse.isButtonPressed(sf::Mouse::Button::Left)) {
        if (globalBounds.contains(mousePos.x, mousePos.y))
            _hasFocus = true;
        else
            _hasFocus = false;
    }
    if (_hasFocus && _currentOutlineColor != _focusOutline) {
        _currentOutlineColor = _focusOutline;
        _colorOutline.setColor(_currentOutlineColor);
    } else if (!_hasFocus && _currentOutlineColor != _unfocusedOutline) {
        _currentOutlineColor = _unfocusedOutline;
        _colorOutline.setColor(_currentOutlineColor);
    }
    _rs.setFillColor(_colorBackground.getColor());
    _rs.setOutlineColor(_colorOutline.getColor());
    _window.draw(_rs);

    if (_content == "") {
        _text.setString(_placeHolder);
        _text.setFillColor(_colorPlaceHolder.getColor());
    } else {
        _text.setString(_content);
        _text.setFillColor(_colorText.getColor());
    }
    _window.draw(_text);

    if (_hasFocus && !((_clock.getElapsedTime().asMilliseconds() / 600) % 2)) {
        if (_content == "")
            _cursor.setPosition(_text.findCharacterPos(0));
        else
            _cursor.setPosition(_text.findCharacterPos(_cursorPos));
        _cursor.setFillColor(_colorText.getColor());
        _window.draw(_cursor);
    }

    _isFull = _text.getGlobalBounds().width + _text.getCharacterSize() + 15 > globalBounds.width;
}

const std::string &InputZone::getAnsiInput()
{
    _stringContent = _content.toAnsiString();
    return (_stringContent);
}

void InputZone::setInput(const std::string &input)
{
    _content = input;
}
