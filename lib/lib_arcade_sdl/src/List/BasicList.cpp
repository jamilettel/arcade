/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** BasicList
*/

#include "List/BasicList.hpp"
#include "SDLError.hpp"

using namespace MySDL;

const float BasicList::_buttonHeight = 30;

SDL_Color BasicList::defaultColor{0x13, 0x13, 0x13, 0xff};
SDL_Color BasicList::defaultAltColor{0x0a, 0x0a, 0x0a, 0xff};
SDL_Color BasicList::defaultFrameColor{0x0a, 0x0a, 0x0a, 0xff};
SDL_Color BasicList::defaultTextColor{0xff, 0xff, 0xff, 0xff};

MySDL::Button::ButtonColor BasicList::defaultButtonColor(SDL_Color{0x0a, 0x5e, 0xee, 0xff},
                                                         SDL_Color{0x1a, 0x6e, 0xf6, 0xff},
                                                         SDL_Color{0x3f, 0x8f, 0xff, 0xff},
                                                         SDL_Color{0x34, 0x34, 0x34, 0xff});

MySDL::Button::ButtonColor BasicList::defaultTextButtonColor(SDL_Color{255, 255, 255, 255},
                                                             SDL_Color{255, 255, 255, 255},
                                                             SDL_Color{255, 255, 255, 255},
                                                             SDL_Color{0x77, 0x77, 0x77, 0xff});

BasicList::BasicList(MySDL::Window &window,
                     const std::vector<std::string> &list,
                     const std::string &title,
                     MySDL::Font &font,
                     int nbDisplayed):
    AList(window, font, list, title), _elementSize(0, 50),
    _nbDisplayed(nbDisplayed), _position(0), _frame(SDL_FRect{0, 0, 0, 0}),
    _elementBackground(SDL_FRect{0, 0, 0, 0}), _elementText(_font, "", 32, _window),
    _frameColor(defaultFrameColor), _textColor(defaultTextColor),
    _normalColor(defaultColor), _altColor(defaultAltColor),
    _buttonColor(defaultButtonColor), _buttonTextColor(defaultTextButtonColor),
    _buttonUp(_window,
              Vector(),
              Vector(),
              _font,
              _buttonColor,
              _buttonTextColor,
              "<",
              [this] () {scroll(-1);}),
    _buttonDown(_window,
                Vector(),
                Vector(),
                _font,
                _buttonColor,
                _buttonTextColor,
                ">",
                [this] () {scroll(1);})
{
    SDL_FRect rect;
    setDrawableObjects();
    scroll(0);

    rect = _buttonUp.getText().getRect();
    _buttonUp.getText().setRotation(90);
    _buttonDown.getText().setRotation(90);
    setListPosition(0);
}

void BasicList::scroll(int to)
{
    int dest = _position;

    if (_prev.has_value()) {
        (*_prev)->scroll(to);
        return;
    }
    if (((to > 0 && _position < static_cast<int>(_list.size()) - _nbDisplayed) ||
         (to < 0 && _position)))
        dest += to;

    if (dest >= static_cast<int>(_list.size()) - _nbDisplayed)
        if (dest > static_cast<int>(_list.size()) - _nbDisplayed)
            dest -= _nbDisplayed;
    if (dest <= 0)
        dest = 0;

    setListPosition(dest);
}

void BasicList::setListPosition(int pos)
{
    if (pos >= static_cast<int>(_list.size()) - _nbDisplayed)
        _buttonDown.setActivation(false);
    else
        _buttonDown.setActivation(true);
    if (pos <= 0)
        _buttonUp.setActivation(false);
    else
        _buttonUp.setActivation(true);
    if (_position == pos)
        return;
    _position = pos;
    if (_next.has_value())
        (*_next)->setListPosition(pos);
    if (_prev.has_value())
        (*_prev)->setListPosition(pos);
}

void BasicList::drawElement(size_t element, const Vector &pos)
{
    _elementBackground.setPosition(pos);

    if ((element) % 2)
        _elementBackground.setColor(_altColor);
    else
        _elementBackground.setColor(_normalColor);

    _window.draw(_elementBackground);

    _elementText.setString(_list[element]);
    SDL_FRect rect = _elementText.getRect();
    // size_t size = _elementText.getCharacterSize();

    _elementText.setPosition(Vector(pos.x + _size.x/2 - rect.w / 2,
                                    pos.y + 25.0f - rect.h / 2.0f));
    _window.draw(_elementText);
}

void BasicList::draw()
{
    Vector pos = _pos;

    if (_next.has_value())
        (*_next)->draw();

    _window.draw(_frame);
    _window.draw(_title);

    for (int i = 0; i < _nbDisplayed; i++) {
        pos.y = _pos.y + (1 + i) * 50 + _buttonHeight;
        if (_position + i < static_cast<int>(_list.size()))
            drawElement(_position + i, pos);
        else {
            if ((i + _position) % 2)
                _elementBackground.setColor(_altColor);
            else
                _elementBackground.setColor(_normalColor);
            _elementBackground.setPosition(pos);
            _window.draw(_elementBackground);
        }
    }

    if (!_prev.has_value()) {
        _buttonUp.draw();
        _buttonDown.draw();
    }
}

void BasicList::update(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEWHEEL) {
        Vector mousePos;
        int x = 0, y = 0;
        SDL_FRect frameRect = _frame.getRect();
        SDL_GetMouseState(&x, &y);
        mousePos.x = x;
        mousePos.y = y;

        if (mousePos.x >= frameRect.x && mousePos.x < frameRect.x + frameRect.w &&
            mousePos.y >= frameRect.y && mousePos.y < frameRect.y + frameRect.h)
            scroll(-event.wheel.y);
    }
    if (_next.has_value())
        (*_next)->update(event);
    _buttonUp.update(event);
    _buttonDown.update(event);
}

void BasicList::setDrawableObjects()
{
    size_t size = 42;

    _size.y = (_nbDisplayed + 1) * 50 + _buttonHeight * 2;
    _frame.setColor(_frameColor);
    _frame.setColor(_frameColor);
    _frame.setPosition(_pos);
    _frame.setSize(_size);

    _title.setCharacterSize(size);
    _title.setColor(_textColor);
    SDL_FRect textBounds = _title.getRect();
    Vector wantedPosition(_pos.x + _elementSize.x/2 - textBounds.w / 2,
                          _pos.y + _elementSize.y/2 - size / 2.5);
    _title.setPosition(wantedPosition);
    _elementBackground.setSize(Vector(_size.x, 50));
    _elementText.setColor(_textColor);
    _buttonUp.setSize(getWidth(), _buttonHeight);
    _buttonUp.setPosition(_pos.x, _pos.y + 50);
    _buttonDown.setSize(getWidth(), _buttonHeight);
    _buttonDown.setPosition(_pos.x, _pos.y + (1 + _nbDisplayed) * 50 + _buttonHeight);
}

void BasicList::setPos(const Vector &pos)
{
    AList::setPos(pos);
    if (_next.has_value())
        (*_next)->setPos(Vector(pos.x + _size.x, pos.y));
    setDrawableObjects();
}

void BasicList::setSize(const Vector &size)
{
    if (size != _size) {
        AList::setSize(size);

        _elementSize.x = size.x;
        if (_next.has_value()) {
            (*_next)->setPos(Vector(_pos.x + _size.x, _pos.y));
            if ((*_next)->getSize().x == 0)
                (*_next)->setSize(size);
        }
        if (_prev.has_value()) {
            (*_prev)->setSize((*_prev)->getSize()); // refresh first
        }
    }
    setDrawableObjects();
}

float BasicList::getWidth() const
{
    float size = _size.x;

    if (_next.has_value())
        size += (*_next)->getWidth();
    return (size);
}

void BasicList::setList(const std::vector<std::string> &list)
{
    AList::setList(list);
    scroll(0);
}

int BasicList::getNbDisplayed() const
{
    return (_nbDisplayed);
}

void BasicList::setNbDisplayed(int nbDisplayed)
{
    _nbDisplayed = nbDisplayed;
}

void BasicList::setColor(const MySDL::Button::ButtonColor &button,
                         const MySDL::Button::ButtonColor &text)
{
    _buttonColor = button;
    _buttonTextColor = text;
}

void BasicList::setColor(const SDL_Color &frame, const SDL_Color &text,
                         const SDL_Color &color, const SDL_Color &altColor)
{
    _frameColor = frame;
    _textColor = text;
    _normalColor = color;
    _altColor = altColor;
}

size_t BasicList::getColsNumber() const
{
    if (_next.has_value())
        return ((*_next)->getColsNumber() + 1);
    return (1);
}

BasicList &BasicList::getColumn(size_t nb)
{
    if (!nb)
        return (*this);
    if (!_next.has_value())
        throw arc::SDLError("List: " + std::to_string(nb) + " is out of bounds");
    return ((*_next)->getColumn(nb - 1));
}
