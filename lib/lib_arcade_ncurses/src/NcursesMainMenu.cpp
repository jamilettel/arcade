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
    _mainMenuBox["MainTitle"] = subwin(stdscr, 10, 63, 0, ((COLS - 63) / 2));
}

NcursesMainMenu::~NcursesMainMenu()
{
}

void NcursesMainMenu::display()
{
    this->displayMainTitle();
}

void NcursesMainMenu::displayMainTitle()
{
    wattron(_mainMenuBox["MainTitle"], COLOR_PAIR(GREEN_BLACK));
    mvwprintw(_mainMenuBox["MainTitle"], 2, 1, "   /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$ ");
    mvwprintw(_mainMenuBox["MainTitle"], 3, 1, "  /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$_____/ ");
    mvwprintw(_mainMenuBox["MainTitle"], 4, 1, " | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\ $$| $$  \\ $$| $$ ");
    mvwprintw(_mainMenuBox["MainTitle"], 5, 1, " | $$$$$$$$| $$$$$$$/| $$      | $$$$$$$$| $$  | $$| $$$$$ ");
    mvwprintw(_mainMenuBox["MainTitle"], 6, 1, " | $$__  $$| $$__  $$| $$      | $$__  $$| $$  | $$| $$__/ ");
    mvwprintw(_mainMenuBox["MainTitle"], 7, 1, " | $$  | $$| $$  \\ $$| $$    $$| $$  | $$| $$  | $$| $$ ");
    mvwprintw(_mainMenuBox["MainTitle"], 8, 1, " | $$  | $$| $$  | $$|  $$$$$$/| $$  | $$| $$$$$$$/| $$$$$$$$ ");
    mvwprintw(_mainMenuBox["MainTitle"], 9, 1, " |__/  |__/|__/  |__/ \\______/ |__/  |__/|_______/ |________/ ");
    wattroff(_mainMenuBox["MainTitle"], COLOR_PAIR(GREEN_BLACK));
    wnoutrefresh(_mainMenuBox["MainTitle"]);
}

void NcursesMainMenu::displayMainMenu()
{
}