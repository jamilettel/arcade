/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "NcursesMainMenu.hpp"

#include <iostream>

using namespace arc;

NcursesMainMenu::NcursesMainMenu(NcursesGraphical &mainLib) : _lib(mainLib), _activeMenu(1), _controls(_lib.getHowToPlay())
{
    _termColor = has_colors();
    if (supportColor()) {
        _lib.addColor({7, 29, 27, 1});
        _lib.addColor({0, 0, 0, 1});
        _lib.initPairColor(_lib.getColor({0, 0, 0, 1}), _lib.getColor({7, 29, 27, 1}));
        wbkgd(stdscr, COLOR_PAIR(_lib.getPairColor(_lib.getColor({0, 0, 0, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
}

NcursesMainMenu::~NcursesMainMenu()
{
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        delwin(win.second);
    });
    _windows.clear();
}

void NcursesMainMenu::display()
{
    erase();
    this->displayMainTitle();
    this->displayCommandUsername();
    this->displayMenuGames();
    this->displayMenuGraphics();
    this->displayInfo();
}

void NcursesMainMenu::update()
{
    std::pair<Event::Type, Event::Key> event;

    event.first = _lib.getEventType();
    event.second = _lib.getKeyPressed();
    if (event.second == Event::Key::DOWN) {
        if (_activeMenu == 1 && _chosenGame + 1 != _listGames->size())
            _chosenGame++;
        else if (_activeMenu == 2 && _chosenGraphics + 1 != _listGraphics->size())
            _chosenGraphics++;
    }
    if (event.second == Event::Key::UP) {
        if (_activeMenu == 1 && _chosenGame != 0)
            _chosenGame--;
        else if (_activeMenu == 2 && _chosenGraphics != 0)
            _chosenGraphics--;
    }
    if (event.second == Event::Key::LEFT)
        _activeMenu = 1;
    if (event.second == Event::Key::RIGHT)
        _activeMenu = 2;
    if (event.second == Event::Key::ENTER && _activeMenu == 1) {
        _ftGames.value()(_listGames->at(_chosenGame));
        _lib._playFct.value()();
    }
    if (event.second == Event::Key::ENTER && _activeMenu == 2) {
        _ftGraphics.value()(_listGraphics->at(_chosenGraphics));
    }
    if (event.second == Event::Key::U) {
        this->promptUsername();
    }
}

void NcursesMainMenu::refresh()
{
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        wnoutrefresh(win.second);
    });
    ::refresh();
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

bool NcursesMainMenu::supportColor() const
{
    return _termColor;
}

void NcursesMainMenu::displayMainTitle() const
{
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(stdscr, COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    mvwprintw(stdscr, 3, COLS / 2 - 62 / 2, "   /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$ ");
    mvwprintw(stdscr, 4, COLS / 2 - 62 / 2, "  /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$_____/ ");
    mvwprintw(stdscr, 5, COLS / 2 - 62 / 2, " | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\ $$| $$  \\ $$| $$ ");
    mvwprintw(stdscr, 6, COLS / 2 - 62 / 2, " | $$$$$$$$| $$$$$$$/| $$      | $$$$$$$$| $$  | $$| $$$$$ ");
    mvwprintw(stdscr, 7, COLS / 2 - 62 / 2, " | $$__  $$| $$__  $$| $$      | $$__  $$| $$  | $$| $$__/ ");
    mvwprintw(stdscr, 8, COLS / 2 - 62 / 2, " | $$  | $$| $$  \\ $$| $$    $$| $$  | $$| $$  | $$| $$ ");
    mvwprintw(stdscr, 9, COLS / 2 - 62 / 2, " | $$  | $$| $$  | $$|  $$$$$$/| $$  | $$| $$$$$$$/| $$$$$$$$ ");
    mvwprintw(stdscr, 10, COLS / 2 - 62 / 2, " |__/  |__/|__/  |__/ \\______/ |__/  |__/|_______/ |________/ ");
    wattroff(stdscr, COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesMainMenu::displayMenuGames()
{
    unsigned int i = 0;
    delwin(_windows["MenuGames"]);
    _windows["MenuGames"] = subwin(stdscr, 20, 30, LINES / 2 - 20 / 2, COLS / 2 - 40);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["MenuGames"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["MenuGames"], 0, 0);
    mvwprintw(_windows["MenuGames"], 0, 0, "Games");
    mvwprintw(_windows["MenuGames"], 19, 0, "Press enter to play");
    wattroff(_windows["MenuGames"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));

    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["MenuGames"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }

    for (const std::string &game : _listGames.value()) {
        if (_chosenGame == i / 3 && _activeMenu == 1)
            wattron(_windows["MenuGames"], A_REVERSE);
        mvwprintw(_windows["MenuGames"], i + 3, 30 / 2 - game.substr(0, game.find_last_of('.')).substr(game.find_last_of('_') + 1).length() / 2, game.substr(0, game.find_last_of('.')).substr(game.find_last_of('_') + 1).c_str());
        wattroff(_windows["MenuGames"], A_REVERSE);
        i += 3;
    }
    wattroff(_windows["MenuGames"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesMainMenu::displayMenuGraphics()
{
    unsigned int i = 0;
    delwin(_windows["MenuGraphics"]);
    _windows["MenuGraphics"] = subwin(stdscr, 20, 30, LINES / 2 - 20 / 2, COLS / 2 + 10);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["MenuGraphics"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["MenuGraphics"], 0, 0);
    mvwprintw(_windows["MenuGraphics"], 0, 0, "Graphics");
    mvwprintw(_windows["MenuGraphics"], 19, 0, "Enter to change graphic mode");
    wattroff(_windows["MenuGraphics"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));

    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["MenuGraphics"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }

    for (const std::string &graphic : _listGraphics.value()) {
        if (_chosenGraphics == i / 3 && _activeMenu == 2)
            wattron(_windows["MenuGraphics"], A_REVERSE);
        mvwprintw(_windows["MenuGraphics"], i + 3, 30 / 2 - graphic.substr(0, graphic.find_last_of('.')).substr(graphic.find_last_of('_') + 1).length() / 2, graphic.substr(0, graphic.find_last_of('.')).substr(graphic.find_last_of('_') + 1).c_str());
        wattroff(_windows["MenuGraphics"], A_REVERSE);
        i += 3;
    }
    wattroff(_windows["MenuGraphics"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesMainMenu::displayInfo()
{
    int i = 2;
    delwin(_windows["InfoBox"]);
    _windows["InfoBox"] = subwin(stdscr, 10, 30, LINES / 2 + 12, COLS / 3 + 18);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["InfoBox"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["InfoBox"], 0, 0);
    mvwprintw(_windows["InfoBox"], 0, 0, "Some Controls in game");
    wattroff(_windows["InfoBox"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["InfoBox"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }

    for (const std::pair<std::string, std::string> &control : *_controls) {
        mvwprintw(_windows["InfoBox"], i, 2, control.first.c_str());
        mvwprintw(_windows["InfoBox"], i, control.first.length() + 3, ":");
        mvwprintw(_windows["InfoBox"], i, control.first.length() + 5, control.second.c_str());
        i++;
    }
    wattroff(_windows["InfoBox"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesMainMenu::displayCommandUsername()
{
    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(stdscr, COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    wattron(stdscr, A_REVERSE);
    mvwprintw(stdscr, 15, COLS / 2 - 29 / 2, "Press U to choose a username.");
    wattroff(stdscr, A_REVERSE);
    wattroff(stdscr, COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesMainMenu::promptUsername()
{
    int ch;
    _userField[0] = new_field(1, 20, LINES / 2, COLS / 2 - 10, 0, 0);
    _userField[1] = nullptr;
    
    set_field_opts(_userField[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(_userField[1], A_UNDERLINE);

    _userForm = new_form(_userField);
    post_form(_userForm);
    refresh();
    mvprintw(LINES / 2, COLS / 2 - 20, "Username:");

    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        attron(COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    mvprintw(3, COLS / 2 - 153 / 2, " ________           __                                                                                                                                  ");
    mvprintw(4, COLS / 2 - 153 / 2, "|        \\         |  \\                                                                                                                                 ");
    mvprintw(5, COLS / 2 - 153 / 2, "| $$$$$$$$_______ _| $$_    ______    ______          ______         __    __   _______   ______    ______   _______    ______   ______ ____    ______  ");
    mvprintw(6, COLS / 2 - 153 / 2, "| $$__   |       \\   $$ \\  /      \\  /      \\        |      \\       |  \\  |  \\ /       \\ /      \\  /      \\ |       \\  |      \\ |      \\    \\  /      \\ ");
    mvprintw(7, COLS / 2 - 153 / 2, "| $$  \\  | $$$$$$$\\$$$$$$ |  $$$$$$\\|  $$$$$$\\        \\$$$$$$\\      | $$  | $$|  $$$$$$$|  $$$$$$\\|  $$$$$$\\| $$$$$$$\\  \\$$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$\\");
    mvprintw(8, COLS / 2 - 153 / 2, "| $$$$$  | $$  | $$| $$ __| $$    $$| $$   \\$$       /      $$      | $$  | $$ \\$$    \\ | $$    $$| $$   \\$$| $$  | $$ /      $$| $$ | $$ | $$| $$    $$");
    mvprintw(9, COLS / 2 - 153 / 2, "| $$_____| $$  | $$| $$|  \\ $$$$$$$$| $$            |  $$$$$$$      | $$__/ $$ _\\$$$$$$\\| $$$$$$$$| $$      | $$  | $$|  $$$$$$$| $$ | $$ | $$| $$$$$$$$");
    mvprintw(10, COLS / 2 - 153 / 2, "| $$     \\ $$  | $$ \\$$  $$\\$$     \\| $$             \\$$    $$       \\$$    $$|       $$ \\$$     \\| $$      | $$  | $$ \\$$    $$| $$ | $$ | $$ \\$$     \\");
    mvprintw(11, COLS / 2 - 153 / 2, " \\$$$$$$$$\\$$   \\$$  \\$$$$  \\$$$$$$$ \\$$              \\$$$$$$$        \\$$$$$$  \\$$$$$$$   \\$$$$$$$ \\$$       \\$$   \\$$  \\$$$$$$$ \\$$  \\$$  \\$$  \\$$$$$$$");
    mvprintw(40, COLS / 2 - 26 / 2, "Enter to validate");
    mvprintw(42, COLS / 2 - 28 / 2, "Escape : Go back to Menu");
    attroff(COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));

    while((ch = getch()) != 27) {
        if (ch == 10) {
            form_driver(_userForm, REQ_NEXT_FIELD);
            form_driver(_userForm, REQ_PREV_FIELD);
            std::string username(field_buffer(_userField[0], 0));
            username.erase(std::remove_if(username.begin(), username.end(), isspace), username.end());
            _lib.setUsername(username);
            break;
        } else if (ch == 127 || ch == KEY_BACKSPACE) {
            form_driver(_userForm, REQ_DEL_PREV);
        } else {
            form_driver(_userForm, ch);
        }
    }

    unpost_form(_userForm);
    free_form(_userForm);
    free_field(_userField[0]);
}
