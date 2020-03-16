/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "NcursesGame.hpp"

using namespace arc;

NcursesGame::NcursesGame(NcursesGraphical &mainLib) : _lib(mainLib), _mapSize(std::pair<size_t, size_t>(0, 0)), _controls(_lib.getHowToPlay())
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
    this->displayMap();
    this->displayCommands();
    this->displayGameInfo();
    this->displayEntities();
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

    wattroff(_windows["Title"], COLOR_PAIR(RED_WHITE));
}

void NcursesGame::setMapSize(size_t height, size_t width)
{
    _mapSize.first = height;
    _mapSize.second = width;
}

void NcursesGame::displayMap()
{
    delwin(_windows["Map"]);
    _windows["Map"] = subwin(stdscr, _mapSize.first, _mapSize.second, LINES / 2 - _mapSize.first / 2, COLS / 2 - _mapSize.second / 2);
    if (supportColor())
        wattron(_windows["Map"], COLOR_PAIR(WHITE_WHITE));
    wbkgd(_windows["Map"], COLOR_PAIR(WHITE_WHITE));
    wattroff(_windows["Map"], COLOR_PAIR(WHITE_WHITE));
}

void NcursesGame::displayCommands()
{
    delwin(_windows["Commands"]);
    _windows["Commands"] = subwin(stdscr, 8, 60, LINES - 10, 10);
    if (supportColor())
        wattron(_windows["Commands"], COLOR_PAIR(WHITE_WHITE));
    wbkgd(_windows["Commands"], COLOR_PAIR(WHITE_WHITE));
    wattroff(_windows["Commands"], COLOR_PAIR(WHITE_WHITE));
}

void NcursesGame::displayGameInfo()
{
    int i = 1;
    int j = 0;
    delwin(_windows["Infos"]);
    _windows["Infos"] = subwin(stdscr, 8, 60, LINES - 10, COLS - 70);
    if (supportColor())
        wattron(_windows["Infos"], COLOR_PAIR(WHITE_WHITE));
    wbkgd(_windows["Infos"], COLOR_PAIR(WHITE_WHITE));
    wattroff(_windows["Infos"], COLOR_PAIR(WHITE_WHITE));
    if (supportColor())
        wattron(_windows["Infos"], COLOR_PAIR(GREEN_WHITE));
    for (const std::pair<std::string, std::string> &control : *_controls) {
        if (i == 7) {
            j = 30;
            i = 1;
        }
        mvwprintw(_windows["Infos"], i, 1 + j, control.first.c_str());
        mvwprintw(_windows["Infos"], i, control.first.length() + 2 + j, ":");
        mvwprintw(_windows["Infos"], i, control.first.length() + 4 + j, control.second.c_str());
        i++;
    }
    wattroff(_windows["Infos"], COLOR_PAIR(GREEN_BLUE));
}

void NcursesGame::displayEntities()
{

}
