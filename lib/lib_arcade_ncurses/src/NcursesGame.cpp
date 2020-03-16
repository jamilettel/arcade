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
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        delwin(win.second);
    });
    _windows.clear();
}

bool NcursesGame::supportColor() const
{
    return _termColor;
}

void NcursesGame::display()
{
    erase();
    this->displayTitleGame();
}

void NcursesGame::refresh()
{
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        wnoutrefresh(win.second);
    });
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

void NcursesGame::setGameTitle(std::string gameTitle)
{
    _gameTitle = gameTitle;
}

void NcursesGame::displayTitleGame()
{
    delwin(_windows["Title"]);
    _windows["Title"] = subwin(stdscr, 5, 30, 2, COLS / 2 - 30 / 2);
    if (supportColor())
        wattron(_windows["Title"], COLOR_PAIR(RED_WHITE));
    wbkgd(_windows["Title"], COLOR_PAIR(RED_WHITE));
    mvwprintw(_windows["Title"], 2, 30 / 2 - _gameTitle.length() / 2, _gameTitle.c_str());

    wattroff(_windows["MenuGames"], COLOR_PAIR(RED_WHITE));
}