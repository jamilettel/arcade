/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "NcursesMainMenu.hpp"

using namespace arc;

NcursesMainMenu::NcursesMainMenu()
{
    this->createMainTitle();
    //this->createMenuGames();
    //this->createMenuGraphics();
    //update_panels();
}

NcursesMainMenu::~NcursesMainMenu()
{
}

void NcursesMainMenu::display()
{
    this->displayMainTitle();
}

void NcursesMainMenu::refresh()
{
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*> &win){
        wrefresh(win.second);
    });
    doupdate();
}

void NcursesMainMenu::createMainTitle()
{
    _windows["MainTitle"] = subwin(stdscr, 10, 63, 0, ((COLS - 63) / 2));
}

void NcursesMainMenu::displayMainTitle()
{
    wattron(_windows["MainTitle"], COLOR_PAIR(GREEN_BLACK));
    mvwprintw(_windows["MainTitle"], 2, 1, "   /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$ ");
    mvwprintw(_windows["MainTitle"], 3, 1, "  /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$_____/ ");
    mvwprintw(_windows["MainTitle"], 4, 1, " | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\ $$| $$  \\ $$| $$ ");
    mvwprintw(_windows["MainTitle"], 5, 1, " | $$$$$$$$| $$$$$$$/| $$      | $$$$$$$$| $$  | $$| $$$$$ ");
    mvwprintw(_windows["MainTitle"], 6, 1, " | $$__  $$| $$__  $$| $$      | $$__  $$| $$  | $$| $$__/ ");
    mvwprintw(_windows["MainTitle"], 7, 1, " | $$  | $$| $$  \\ $$| $$    $$| $$  | $$| $$  | $$| $$ ");
    mvwprintw(_windows["MainTitle"], 8, 1, " | $$  | $$| $$  | $$|  $$$$$$/| $$  | $$| $$$$$$$/| $$$$$$$$ ");
    mvwprintw(_windows["MainTitle"], 9, 1, " |__/  |__/|__/  |__/ \\______/ |__/  |__/|_______/ |________/ ");
    wattroff(_windows["MainTitle"], COLOR_PAIR(GREEN_BLACK));
}

void NcursesMainMenu::createMenuGames()
{
    _windows["Menu1"] = subwin(stdscr, 20, 20, LINES - LINES + 1, COLS - COLS + 1);
    _panel["Menu1"] = new_panel(_windows["Menu1"]);
    set_panel_userptr(_panel["Menu1"], _panel["Menu2"]);

    int startx, starty, width, height;

    getbegyx(_windows["Menu1"], starty, startx);
    getmaxyx(_windows["Menu1"], height, width);

    box(_windows["Menu1"], 0, 0);
    mvwaddch(_windows["Menu1"], 2, 0, ACS_LTEE);
    mvwhline(_windows["Menu1"], 2, 1, ACS_HLINE, width - 2);
    mvwaddch(_windows["Menu1"], 2, width - 1, ACS_RTEE);

    int length, x, y;
    float temp;
    std::string test("Games");

    if(_windows["Menu1"] == NULL)
        _windows["Menu1"] = stdscr;
    getyx(_windows["Menu1"], y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = test.length();
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    wattron(_windows["Menu1"], COLOR_PAIR(GREEN_BLACK));
    mvwprintw(_windows["Menu1"], 0, 0, "%s", "Games");
    wattroff(_windows["Menu1"], COLOR_PAIR(GREEN_BLACK));
}

void NcursesMainMenu::createMenuGraphics()
{
    _windows["Menu2"] = subwin(stdscr, 20, 20, 40, 40);
    _panel["Menu2"] = new_panel(_windows["Menu2"]);
    set_panel_userptr(_panel["Menu2"], _panel["Menu1"]);
}