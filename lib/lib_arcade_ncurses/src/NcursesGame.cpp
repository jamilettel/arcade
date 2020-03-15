/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "NcursesGame.hpp"

using namespace arc;

NcursesGame::NcursesGame(NcursesGraphical &mainLib) : _lib(mainLib)
{
    _termColor = has_colors();
    if (supportColor()) {
        wbkgd(stdscr, COLOR_PAIR(BLACK_BLUE));
    }
}

NcursesGame::~NcursesGame()
{

}

bool NcursesGame::supportColor() const
{
    return _termColor;
}

void NcursesGame::display()
{
    mvprintw(10, 10, "TEST");
}

void NcursesGame::refresh()
{
    ::refresh();
}

void NcursesGame::update()
{

}

void NcursesGame::setListGraphics(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen)
{

}

void NcursesGame::setListGames(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen)
{

}