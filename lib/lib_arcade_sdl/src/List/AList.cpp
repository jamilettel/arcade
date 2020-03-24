/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#include "List/AList.hpp"

using namespace MySDL;

AList::AList(MySDL::Window &window,
             MySDL::Font &font,
             const std::vector<std::string> &list,
             const std::string &title):
    _window(window), _font(font), _list(list), _title(_font, title, 32, _window)
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

const MySDL::Font &AList::getFont() const
{
    return (_font);
}

MySDL::Font &AList::getFont()
{
    return (_font);
}

void AList::setSize(const MySDL::Vector &size)
{
    _size = size;
}

void AList::setPos(const MySDL::Vector &pos)
{
    _pos = pos;
}

const MySDL::Vector &AList::getSize() const
{
    return (_size);
}

const MySDL::Vector &AList::getPos() const
{
    return (_pos);
}
