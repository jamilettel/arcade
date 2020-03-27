/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#include "MySf/List/ButtonList.hpp"

using namespace MySf;

Button::ButtonColor ButtonList::defaultAltColors(sf::Color(0x0a0a0aff),
                                           sf::Color(0x3c3c3cff),
                                           sf::Color(0x5f5f5fff),
                                           sf::Color(0x0a5eeeff));

Button::ButtonColor ButtonList::defaultColors(sf::Color(0x131313ff),
                                        sf::Color(0x3c3c3cff),
                                        sf::Color(0x5f5f5fff),
                                        sf::Color(0x0a5eeeff));

ButtonList::ButtonList(sf::RenderWindow &window,
                       const std::vector<std::string> &list,
                       const std::function<void (const std::string &)> &fct,
                       const std::string &title,
                       sf::Font &font,
                       int nbDisplayed,
                       int chosen):
    BasicList(window, list, title, font, nbDisplayed), _fct(fct), _colors(defaultColors),
    _altColors(defaultAltColors)
{
    setList(list, chosen);
}

void ButtonList::setColors(const Button::ButtonColor &normal,
                           const Button::ButtonColor &alt)
{
    _colors = normal;
    _altColors = alt;
}

void ButtonList::setList(const std::vector<std::string> &list)
{
    setList(list, -1);
}

void ButtonList::setList(const std::vector<std::string> &list, int chosen)
{
    sf::Vector2f pos(_pos.x, _pos.y + 50);
    sf::Vector2f size(_size.x, 50);
    int i = 0;

    BasicList::setList(list);
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
                                  if (_fct)
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

void ButtonList::setChosen()
{
    int chosen = _chosen;
    int i = 0;

    std::for_each(_listButtons.begin(), _listButtons.end(),
                  [&chosen, &i] (std::unique_ptr<Button::RectButton> &button) {
                      button->setActivation(!(chosen == i));
                      i++;
                  });
}

void ButtonList::setFct(const std::function<void (const std::string &)> &fct)
{
    _fct = fct;
}

void ButtonList::drawElement(size_t element, const sf::Vector2f &pos)
{
    _listButtons[element]->setPosition(pos);
    _listButtons[element]->setSize(_size.x, BasicList::_elementSize.y);

    _listButtons[element]->draw();
}
