/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** InputZone
*/

#include "InputZone.hpp"

using namespace MySDL;

InputZone::InputZone(Window &window,
                     const Vector &pos,
                     const Vector &size,
                     Font &font,
                     const std::string &placeHolder):
    _placeHolder(placeHolder), _font(font), _cursorPos(0),
    _cursor(Vector(), Vector()), _hasFocus(false),
    _window(window), _pos(pos), _size(size),
    _colorText(SDL_Color{0x0a, 0x0a, 0x0a, 0xff}),
    _colorBackground(SDL_Color{0xef, 0xef, 0xef, 0xff}),
    _colorOutline(SDL_Color{0x1c, 0x1c, 0x1c, 0xff}),
    _colorPlaceHolder(SDL_Color{0xaa, 0xaa, 0xaa, 0xff}),
    _currentOutlineColor(SDL_Color{0x3c, 0x3c, 0x3c, 0xff}),
    _focusOutline(SDL_Color{0x0a, 0x5e, 0xee, 0xff}),
    _unfocusedOutline(SDL_Color{0x3c, 0x3c, 0x3c, 0xff}),
    _rs(Vector(), Vector()),
    _text(_font, "", 32, _window), _isFull(false), _mouseButtonPressed(false)
{
    applySizeAndPos();
    _currentTicks = SDL_GetTicks();
}

void InputZone::applySizeAndPos()
{
    int textSize = _text.getCharacterSize();

    _rs.setPosition(_pos);
    _rs.setSize(_size);
    _rs.setOutlineThickness(3);
    _text.setPosition(Vector(_pos.x + 5, _pos.y + (_size.y / 2 - textSize / 2)));
    _cursor.setSize(Vector(3, textSize + 5));
}

void InputZone::setPosition(Vector pos)
{
    _pos = pos;
    applySizeAndPos();
}

const Vector &InputZone::getPosition() const
{
    return (_pos);
}

void InputZone::setSize(Vector size)
{
    _size = size;
    applySizeAndPos();
}

const Vector &InputZone::getSize() const
{
    return (_size);
}

void InputZone::setPlaceHolder(const std::string &placeHolder)
{
    _placeHolder = placeHolder;
}

const std::string &InputZone::getPlaceHolder() const
{
    return (_placeHolder);
}

const Font &InputZone::getFont() const
{
    return (_font);
}

const std::string &InputZone::getInput() const
{
    return (_content);
}



void InputZone::setTextColor(const SDL_Color &color)
{
    _colorText.setColor(color);
}

void InputZone::setBackgroundColor(const SDL_Color &color)
{
    _colorBackground.setColor(color);
}

void InputZone::setPlaceHolderColor(const SDL_Color &color)
{
    _colorPlaceHolder.setColor(color);
}

void InputZone::setOutlineColor(const SDL_Color &focused, const SDL_Color &unfocused)
{
    _focusOutline = focused;
    _unfocusedOutline = unfocused;
}

void InputZone::addChar(Uint32 c)
{
    if (!_isFull) {
        std::string str;
        str += static_cast<char>(c);
        _content.insert(_cursorPos, str);
        _cursorPos++;
        _currentTicks = SDL_GetTicks();
    }
}

void InputZone::removeChar()
{
    if (_content.size() && _cursorPos) {
        _content.erase(_cursorPos - 1);
        _cursorPos--;
        _currentTicks = SDL_GetTicks();
    }
}

void InputZone::update(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        _mouseButtonPressed = true;
    else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
        _mouseButtonPressed = false;
    if (!_hasFocus)
        return;
    if (event.type == SDL_TEXTINPUT) {
        if (event.text.text[0] >= ' ' && event.text.text[0] <= '~')
            addChar(event.text.text[0]);
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_DELETE) {
            _cursorPos++;
            removeChar();
        } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
            removeChar();
        } else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_TAB) {
            _hasFocus = false;
        } else if (event.key.keysym.sym == SDLK_LEFT && _cursorPos > 0) {
            _cursorPos--;
            _currentTicks = SDL_GetTicks();
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
            _cursorPos++;
            _currentTicks = SDL_GetTicks();
        }
        if (_cursorPos > _content.size()) {
            _cursorPos = _content.size();
        }
    }
}

void InputZone::draw()
{
    SDL_FRect globalBounds = _rs.getRect();
    Vector mousePos;
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    mousePos.x = x;
    mousePos.y = y;

    if (_mouseButtonPressed) {
        if (mousePos.x >= globalBounds.x && mousePos.x < globalBounds.x + globalBounds.w &&
            mousePos.y >= globalBounds.y && mousePos.y < globalBounds.y + globalBounds.h)
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
    _rs.setColor(_colorBackground.getColor());
    _rs.setOutlineColor(_colorOutline.getColor());
    _window.draw(_rs);

    if (_content == "") {
        _text.setString(_placeHolder);
        _text.setColor(_colorPlaceHolder.getColor());
    } else {
        _text.setString(_content);
        _text.setColor(_colorText.getColor());
    }
    _window.draw(_text);

    if (_hasFocus && !(((SDL_GetTicks() - _currentTicks) / 600) % 2)) {
        Vector pos;
        if (_content == "")
            pos = _text.findCharacterPos(0);
        else
            pos = _text.findCharacterPos(_cursorPos);
        pos.y -= 5;
        _cursor.setPosition(pos);
        _cursor.setColor(_colorText.getColor());
        _window.draw(_cursor);
    }

    _isFull = _text.getRect().w + _text.getCharacterSize() + 15 > globalBounds.w;
}

const std::string &InputZone::getAnsiInput()
{
    return (_content);
}

void InputZone::setInput(const std::string &input)
{
    _content = input;
}
