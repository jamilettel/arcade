/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** BasicList
*/

#include "MySf/List/BasicList.hpp"

using namespace MySf;

const float BasicList::_buttonHeight = 30;

sf::Color BasicList::defaultColor(0x131313ff);
sf::Color BasicList::defaultAltColor(0x0a0a0aff);
sf::Color BasicList::defaultFrameColor(0x0a0a0aff);
sf::Color BasicList::defaultTextColor = sf::Color::White;

MySf::Button::ButtonColor BasicList::defaultButtonColor(sf::Color(0x0a5eeeff),
                                                        sf::Color(0x1a6ef6ff),
                                                        sf::Color(0x3f8fffff),
                                                        sf::Color(0x343434ff));

MySf::Button::ButtonColor BasicList::defaultTextButtonColor(sf::Color::White,
                                                            sf::Color::White,
                                                            sf::Color::White,
                                                            sf::Color(0x777777ff));

BasicList::BasicList(sf::RenderWindow &window,
                     const std::vector<std::string> &list,
                     const std::string &title,
                     sf::Font &font,
                     int nbDisplayed):
    AList(window, font, list, title), _elementSize(0, 50),
    _nbDisplayed(nbDisplayed), _position(0),
    _frameColor(defaultFrameColor), _textColor(defaultTextColor),
    _normalColor(defaultColor), _altColor(defaultAltColor),
    _buttonColor(defaultButtonColor), _buttonTextColor(defaultTextButtonColor),
    _buttonUp(_window,
              sf::Vector2f(),
              sf::Vector2f(),
              _font,
              _buttonColor,
              _buttonTextColor,
              "<",
              [this] () {scroll(-1);}),
    _buttonDown(_window,
                sf::Vector2f(),
                sf::Vector2f(),
                _font,
                _buttonColor,
                _buttonTextColor,
                ">",
                [this] () {scroll(1);})
{
    sf::FloatRect rect;
    setDrawableObjects();
    _elementText.setFont(_font);
    scroll(0);

    rect = _buttonUp.getText().getGlobalBounds();
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

void BasicList::drawElement(size_t element, const sf::Vector2f &pos)
{
    _elementBackground.setPosition(pos);

    if ((element) % 2)
        _elementBackground.setFillColor(_altColor);
    else
        _elementBackground.setFillColor(_normalColor);

    _window.draw(_elementBackground);

    _elementText.setString(_list[element]);
    sf::FloatRect rect = _elementText.getGlobalBounds();
    size_t size = _elementText.getCharacterSize();

    _elementText.setPosition(pos.x + _size.x/2 - rect.width / 2,
                                 pos.y + 25.0f - size / 1.5f);
    _window.draw(_elementText);
}

void BasicList::draw()
{
    sf::Vector2f pos = _pos;

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
                _elementBackground.setFillColor(_altColor);
            else
                _elementBackground.setFillColor(_normalColor);
            _elementBackground.setPosition(pos);
            _window.draw(_elementBackground);
        }
    }

    if (!_prev.has_value()) {
        _buttonUp.draw();
        _buttonDown.draw();
    }
}

void BasicList::update(const sf::Event &event)
{
    if (event.type == sf::Event::EventType::MouseWheelScrolled) {
        sf::Vector2i mousePos = _mouse.getPosition(_window);

        if (_frame.getGlobalBounds().contains(mousePos.x, mousePos.y))
            scroll(-event.mouseWheelScroll.delta);
    }
    if (_next.has_value())
        (*_next)->update(event);
}

void BasicList::setDrawableObjects()
{
    size_t size = 42;

    _size.y = (_nbDisplayed + 1) * 50 + _buttonHeight * 2;
    _frame.setFillColor(_frameColor);
    _frame.setFillColor(_frameColor);
    _frame.setPosition(_pos);
    _frame.setSize(_size);

    _title.setCharacterSize(size);
    _title.setFillColor(_textColor);
    sf::FloatRect textBounds = _title.getGlobalBounds();
    sf::Vector2f wantedPosition(_pos.x + _elementSize.x/2 - textBounds.width / 2,
                                _pos.y + _elementSize.y/2 - size / 2.5);
    _title.move(wantedPosition.x - textBounds.left, wantedPosition.y - textBounds.top);
    _elementBackground.setSize(sf::Vector2f(_size.x, 50));
    _elementText.setFillColor(_textColor);
    _buttonUp.setSize(getWidth(), _buttonHeight);
    _buttonUp.setPosition(_pos.x, _pos.y + 50);
    _buttonDown.setSize(getWidth(), _buttonHeight);
    _buttonDown.setPosition(_pos.x, _pos.y + (1 + _nbDisplayed) * 50 + _buttonHeight);
}

void BasicList::setPos(const sf::Vector2f &pos)
{
    AList::setPos(pos);
    if (_next.has_value())
        (*_next)->setPos(sf::Vector2f(pos.x + _size.x, pos.y));
    setDrawableObjects();
}

void BasicList::setSize(const sf::Vector2f &size)
{
    if (size != _size) {
        AList::setSize(size);

        _elementSize.x = size.x;
        if (_next.has_value()) {
            (*_next)->setPos(sf::Vector2f(_pos.x + _size.x, _pos.y));
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

void BasicList::setColor(const MySf::Button::ButtonColor &button,
                         const MySf::Button::ButtonColor &text)
{
    _buttonColor = button;
    _buttonTextColor = text;
}

void BasicList::setColor(const sf::Color &frame, const sf::Color &text,
                         const sf::Color &color, const sf::Color &altColor)
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
        throw Error("List", std::to_string(nb) + " is out of bounds");
    return ((*_next)->getColumn(nb - 1));
}
