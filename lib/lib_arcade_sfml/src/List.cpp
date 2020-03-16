/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#include "List.hpp"

using namespace MySf;

Button::ButtonColor List::defaultAltColors(sf::Color(0x0a0a0aff),
                                           sf::Color(0x3c3c3cff),
                                           sf::Color(0x5f5f5fff),
                                           sf::Color(0x0a5eeeff));

Button::ButtonColor List::defaultColors(sf::Color(0x131313ff),
                                        sf::Color(0x3c3c3cff),
                                        sf::Color(0x5f5f5fff),
                                        sf::Color(0x0a5eeeff));

sf::Color List::defaultFrameColor(0x0a0a0aff);
sf::Color List::defaultTextColor(0xfcfcfcff);

List::List(sf::RenderWindow &window,
                 const std::vector<std::string> &list,
                 const std::function<void (const std::string &)> &fct,
                 const std::string &title,
                 sf::Font &font,
                 int chosen):
    _window(window), _font(font), _fct(fct), _colors(defaultColors),
    _altColors(defaultAltColors), _frameColor(defaultFrameColor), _textColor(defaultTextColor),
    _title(title, _font)
{
    setList(list, chosen);
    setDrawableObjects();
}

void List::setColors(const Button::ButtonColor &normal,
                           const Button::ButtonColor &alt,
                           const sf::Color &frame,
                           const sf::Color &text)
{
    _colors = normal;
    _altColors = alt;
    _frameColor = frame;
    _textColor = text;
}

void List::setList(const std::vector<std::string> &list, int chosen)
{
    sf::Vector2f pos(_pos.x, _pos.y + 50);
    sf::Vector2f size(_size.x, 50);
    int i = 0;

    _list = list;
    _listButtons.clear();
    _listButtons.reserve(list.size());
    std::for_each(list.begin(), list.end(),
                  [this, &i, &pos, &size] (const std::string &elem) {
                      Button::ButtonColor &colors = (i % 2) ? _altColors : _colors;

                      _listButtons.emplace_back(
                          std::make_unique<Button::RectButton>(
                              _window,
                              pos,
                              size,
                              _font,
                              colors,
                              sf::Color::White,
                              elem,
                              [this, i, elem] () {
                                  _fct(elem);
                                  _chosen = i;
                                  setChosen();
                              }
                              ));
                      i++;
                      pos.y += 50;
                  });
    _chosen = chosen;
    if (_chosen >=0 && _chosen < static_cast<int>(_listButtons.size()))
        _listButtons[_chosen]->setActivation(false);
}

void List::setChosen()
{
    int chosen = _chosen;
    int i = 0;

    std::for_each(_listButtons.begin(), _listButtons.end(),
                  [&chosen, &i] (std::unique_ptr<Button::RectButton> &button) {
                      button->setActivation(!(chosen == i));
                      i++;
                  });
}

const std::vector<std::string> &List::getList() const
{
    return (_list);
}

void List::setFct(const std::function<void (const std::string &)> &fct)
{
    _fct = fct;
}

const std::string List::getTitle() const
{
    return (_title.getString());
}

void List::setTitle(const std::string& title)
{
    _title.setString(title);
}

const sf::Font &List::getFont() const
{
    return (_font);
}

sf::Font &List::getFont()
{
    return (_font);
}

void List::setSize(const sf::Vector2f &size)
{
    _size = size;
    setDrawableObjects();
}

void List::setPos(const sf::Vector2f &pos)
{
    _pos = pos;
    setDrawableObjects();
}

const sf::Vector2f &List::getSize() const
{
    return (_size);
}

const sf::Vector2f &List::getPos() const
{
    return (_pos);
}

void List::setDrawableObjects()
{
    _size.y = (_listButtons.size() + 1) * 50;
    _frame.setFillColor(_frameColor);
    _frame.setFillColor(_frameColor);
    _frame.setPosition(_pos);
    _frame.setSize(_size);
    _title.setFillColor(_textColor);
    _title.setPosition(_pos.x + 5, _pos.y - 3);
    _title.setStyle(sf::Text::Bold);
    _title.setCharacterSize(42);

    sf::Vector2f pos(_pos.x, _pos.y + 50);
    sf::Vector2f size(_size.x, 50);
    std::for_each(_listButtons.begin(), _listButtons.end(),
                  [&pos, &size] (std::unique_ptr<Button::RectButton> &button) {
                      button->setPosition(pos);
                      button->setSize(size);
                      pos.y += 50;
                  });
}

void List::draw()
{
    _window.draw(_frame);
    _window.draw(_title);
    std::for_each(_listButtons.begin(), _listButtons.end(),
                  [] (std::unique_ptr<Button::RectButton> &button) {
                      button->draw();
                  });
}
