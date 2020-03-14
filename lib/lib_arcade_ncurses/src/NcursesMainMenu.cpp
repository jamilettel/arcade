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
    //_panel["Menu1"] = new_panel(_windows["Menu1"]);
    //set_panel_userptr(_panel["Menu1"], _panel["Menu2"]);
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
    //this->createMenuGames();
}

void NcursesMainMenu::refresh()
{
    //update_panels();
    //std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*> &win){
    //    wnoutrefresh(win.second);
    //});
    //::refresh();
    //doupdate();
}

void NcursesMainMenu::createMainTitle()
{
}

void NcursesMainMenu::displayMainTitle()
{
    wattron(stdscr, COLOR_PAIR(GREEN_BLACK));
    mvwprintw(stdscr, 3, COLS / 2 - 62 / 2, "   /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$ ");
    mvwprintw(stdscr, 4, COLS / 2 - 62 / 2, "  /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$_____/ ");
    mvwprintw(stdscr, 5, COLS / 2 - 62 / 2, " | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\ $$| $$  \\ $$| $$ ");
    mvwprintw(stdscr, 6, COLS / 2 - 62 / 2, " | $$$$$$$$| $$$$$$$/| $$      | $$$$$$$$| $$  | $$| $$$$$ ");
    mvwprintw(stdscr, 7, COLS / 2 - 62 / 2, " | $$__  $$| $$__  $$| $$      | $$__  $$| $$  | $$| $$__/ ");
    mvwprintw(stdscr, 8, COLS / 2 - 62 / 2, " | $$  | $$| $$  \\ $$| $$    $$| $$  | $$| $$  | $$| $$ ");
    mvwprintw(stdscr, 9, COLS / 2 - 62 / 2, " | $$  | $$| $$  | $$|  $$$$$$/| $$  | $$| $$$$$$$/| $$$$$$$$ ");
    mvwprintw(stdscr, 10, COLS / 2 - 62 / 2, " |__/  |__/|__/  |__/ \\______/ |__/  |__/|_______/ |________/ ");
    wattroff(stdscr, COLOR_PAIR(GREEN_BLACK));
}

void NcursesMainMenu::createMenuGames()
{

    /*
        int startx, starty, width, height;

        getbegyx(_windows["Menu1"], starty, startx);
        getmaxyx(_windows["Menu1"], height, width);

        //box(_windows["Menu1"], ACS_VLINE, ACS_HLINE);
        //mvwaddch(_windows["Menu1"], 2, 0, ACS_LTEE);
        //mvwhline(_windows["Menu1"], 2, 1, ACS_HLINE, width - 2);
        //mvwaddch(_windows["Menu1"], 2, width - 1, ACS_RTEE);

        int length, x, y;
        float temp;
        std::string test("Games");

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
        */
    wattron(_windows["Menu1"], COLOR_PAIR(GREEN_BLACK));
    mvwprintw(_windows["Menu1"], 10, 0, "GAMES");
    wattroff(_windows["Menu1"], COLOR_PAIR(GREEN_BLACK));
}

void NcursesMainMenu::createMenuGraphics()
{
    _windows["Menu2"] = newwin(20, 20, 40, 40);
    _panel["Menu2"] = new_panel(_windows["Menu2"]);
    set_panel_userptr(_panel["Menu2"], _panel["Menu1"]);
}