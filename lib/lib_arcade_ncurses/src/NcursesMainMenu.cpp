/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "NcursesMainMenu.hpp"

#include <iostream>

using namespace arc;

NcursesMainMenu::NcursesMainMenu(NcursesGraphical &mainLib) : _lib(mainLib)
{
    _termColor = has_colors();
    if (supportColor()) {
        wbkgd(stdscr, COLOR_PAIR(BLACK_BLUE));
    }
}

void NcursesMainMenu::display()
{
    this->displayMainTitle();
    this->createMenuGames();
    this->createMenuGraphics();
}

void NcursesMainMenu::update()
{
    std::pair<Event::Type, Event::Key> event;

    event.first = _lib.getEventType();
    event.second = _lib.getKeyPressed();
    if (event.second == Event::Key::DOWN && _chosenGame + 1 != _listGames->size())
        _chosenGame++;
    if (event.second == Event::Key::UP && _chosenGame != 0)
        _chosenGame--;
}

void NcursesMainMenu::refresh()
{
    ::refresh();
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        wrefresh(win.second);
    });
}

void NcursesMainMenu::setListGames(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen)
{
    _listGames = name;
    _ftGames = fct;
    if (chosen == -1)
        _chosenGame = 0;
    else
        _chosenGame = chosen;
}

void NcursesMainMenu::setListGraphics(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen)
{
    _listGraphics = name;
    _ftGraphics = fct;
    if (chosen == -1)
        _chosenGraphics = 0;
    else
        _chosenGraphics = chosen;
}

bool NcursesMainMenu::supportColor()
{
    return _termColor;
}

void NcursesMainMenu::displayMainTitle()
{
    if (has_colors())
        wattron(stdscr, COLOR_PAIR(YELLOW_BLUE));
    mvwprintw(stdscr, 3, COLS / 2 - 62 / 2, "   /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$ ");
    mvwprintw(stdscr, 4, COLS / 2 - 62 / 2, "  /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$_____/ ");
    mvwprintw(stdscr, 5, COLS / 2 - 62 / 2, " | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\ $$| $$  \\ $$| $$ ");
    mvwprintw(stdscr, 6, COLS / 2 - 62 / 2, " | $$$$$$$$| $$$$$$$/| $$      | $$$$$$$$| $$  | $$| $$$$$ ");
    mvwprintw(stdscr, 7, COLS / 2 - 62 / 2, " | $$__  $$| $$__  $$| $$      | $$__  $$| $$  | $$| $$__/ ");
    mvwprintw(stdscr, 8, COLS / 2 - 62 / 2, " | $$  | $$| $$  \\ $$| $$    $$| $$  | $$| $$  | $$| $$ ");
    mvwprintw(stdscr, 9, COLS / 2 - 62 / 2, " | $$  | $$| $$  | $$|  $$$$$$/| $$  | $$| $$$$$$$/| $$$$$$$$ ");
    mvwprintw(stdscr, 10, COLS / 2 - 62 / 2, " |__/  |__/|__/  |__/ \\______/ |__/  |__/|_______/ |________/ ");
    wattroff(stdscr, COLOR_PAIR(YELLOW_BLUE));
}

void NcursesMainMenu::createMenuGames()
{
    int i = 0;
    _windows["MenuGames"] = subwin(stdscr, 20, 30, LINES / 2 - 20 / 2, COLS / 2 - 40);
    if (supportColor())
        wattron(_windows["MenuGames"], COLOR_PAIR(YELLOW_BLUE));
    box(_windows["MenuGames"], 0, 0);
    mvwprintw(_windows["MenuGames"], 0, 0, "Games");
    wattroff(_windows["MenuGames"], COLOR_PAIR(YELLOW_BLUE));

    for (const std::string &game : _listGames.value()) {
        if (_chosenGame == i / 3)
            wattron(_windows["MenuGames"], A_REVERSE);
        mvwprintw(_windows["MenuGames"], i + 3, 30 / 2 - game.substr(0, game.find_last_of('.')).substr(game.find_last_of('_') + 1).length() / 2, game.substr(0, game.find_last_of('.')).substr(game.find_last_of('_') + 1).c_str());
        wattroff(_windows["MenuGames"], A_REVERSE);
        i += 3;
    }
}

void NcursesMainMenu::createMenuGraphics()
{
    int i = 0;
    _windows["MenuGraphics"] = subwin(stdscr, 20, 30, LINES / 2 - 20 / 2, COLS / 2 + 10);
    if (supportColor())
        wattron(_windows["MenuGraphics"], COLOR_PAIR(YELLOW_BLUE));
    box(_windows["MenuGraphics"], 0, 0);
    mvwprintw(_windows["MenuGraphics"], 0, 0, "Graphics");
    if (supportColor())
        wattroff(_windows["MenuGraphics"], COLOR_PAIR(YELLOW_BLUE));
    for (const std::string &graphic : _listGraphics.value()) {
        if (_chosenGraphics == i / 3)
            wattron(_windows["MenuGraphics"], A_REVERSE);
        mvwprintw(_windows["MenuGraphics"], i + 3, 30 / 2 - graphic.substr(0, graphic.find_last_of('.')).substr(graphic.find_last_of('_') + 1).length() / 2, graphic.substr(0, graphic.find_last_of('.')).substr(graphic.find_last_of('_') + 1).c_str());
        wattroff(_windows["MenuGraphics"], A_REVERSE);
        i += 3;
    }
}