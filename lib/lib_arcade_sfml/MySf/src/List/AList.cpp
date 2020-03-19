/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#include "MySf/List/AList.hpp"

using namespace MySf;

AList::AList(sf::RenderWindow &window,
             sf::Font &font,
             const std::vector<std::string> &list,
             const std::string &title):
    _window(window), _font(font), _list(list), _title(title, _font)
{}

const std::vector<std::string> &AList::getList() const
{
    return (_list);
}

void AList::setList(const std::vector<std::string> &list)
{
    _list = list;
}

const std::string AList::getTitle() const
{
    return (_title.getString());
}

void AList::setTitle(const std::string& title)
{
    _title.setString(title);
}

const sf::Font &AList::getFont() const
{
    return (_font);
}

sf::Font &AList::getFont()
{
    return (_font);
}

void AList::setSize(const sf::Vector2f &size)
{
    _size = size;
}

void AList::setPos(const sf::Vector2f &pos)
{
    _pos = pos;
}

const sf::Vector2f &AList::getSize() const
{
    return (_size);
}

const sf::Vector2f &AList::getPos() const
{
    return (_pos);
}
