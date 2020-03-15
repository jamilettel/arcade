/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "NcursesMainMenu.hpp"

#include <iostream>

using namespace arc;

NcursesMainMenu::NcursesMainMenu(NcursesGraphical &mainLib)
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

void NcursesMainMenu::refresh()
{
    ::refresh();
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        wrefresh(win.second);
    });
}

void NcursesMainMenu::setListGames(std::vector<std::string> name, std::function<void (const std::string &)> fct, int chosen)
{
    _listGames = name;
    _ftGames = fct;
    _chosenGame = chosen;
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
    if (has_colors())
        wattroff(stdscr, COLOR_PAIR(YELLOW_BLUE));
}

void NcursesMainMenu::createMenuGames()
{
    _windows["MenuGames"] = subwin(stdscr, 20, 30, LINES / 2 - 20 / 2, COLS / 2 - 40);
    if (supportColor())
        wattron(_windows["MenuGames"], COLOR_PAIR(YELLOW_BLUE));
    box(_windows["MenuGames"], 0, 0);
    mvwprintw(_windows["MenuGames"], 0, 0, "Games");
    if (supportColor())
        wattroff(_windows["MenuGames"], COLOR_PAIR(YELLOW_BLUE));
}

void NcursesMainMenu::createMenuGraphics()
{
    _windows["MenuGraphics"] = subwin(stdscr, 20, 30, LINES / 2 - 20 / 2, COLS / 2 + 10);
    box(_windows["MenuGraphics"], 0, 0);
    mvwprintw(_windows["MenuGraphics"], 0, 0, "Graphics");
}