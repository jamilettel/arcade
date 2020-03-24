/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#include "List/ButtonList.hpp"

using namespace MySDL;

Button::ButtonColor ButtonList::defaultAltColors(SDL_Color{0x0a, 0x0a, 0x0a, 0xff},
                                                 SDL_Color{0x3c, 0x3c, 0x3c, 0xff},
                                                 SDL_Color{0x5f, 0x5f, 0x5f, 0xff},
                                                 SDL_Color{0x0a, 0x5e, 0xee, 0xff});

Button::ButtonColor ButtonList::defaultColors(SDL_Color{0x13, 0x13, 0x13, 0xff},
                                              SDL_Color{0x3c, 0x3c, 0x3c, 0xff},
                                              SDL_Color{0x5f, 0x5f, 0x5f, 0xff},
                                              SDL_Color{0x0a, 0x5e, 0xee, 0xff});

ButtonList::ButtonList(Window &window,
                       const std::vector<std::string> &list,
                       const std::function<void (const std::string &)> &fct,
                       const std::string &title,
                       Font &font,
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
    Vector pos(_pos.x, _pos.y + 50);
    Vector size(_size.x, 50);
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
                              SDL_Color{255, 255, 255, 255},
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

void ButtonList::drawElement(size_t element, const Vector &pos)
{
    _listButtons[element]->setPosition(pos);
    _listButtons[element]->setSize(_size.x, BasicList::_elementSize.y);

    _listButtons[element]->draw();
}

void ButtonList::update(const SDL_Event &event)
{
    for (int i = 0; i < _nbDisplayed; i++) {
        if (i + _position >= static_cast<int>(_list.size()))
            return;
        _listButtons[i + _position]->update(event);
    }
    BasicList::update(event);
}
