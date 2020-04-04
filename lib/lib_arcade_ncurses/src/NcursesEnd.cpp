/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "NcursesEnd.hpp"

using namespace arc;

NcursesEnd::NcursesEnd(NcursesGraphical &mainLib) : _lib(mainLib)
{
    _termColor = has_colors();
    if (supportColor()) {
        _lib.addColor({7, 29, 27, 1});
        _lib.addColor({0, 0, 0, 1});
        _lib.initPairColor(_lib.getColor({0, 0, 0, 1}), _lib.getColor({7, 29, 27, 1}));
        wbkgd(stdscr, COLOR_PAIR(_lib.getPairColor(_lib.getColor({0, 0, 0, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
}

NcursesEnd::~NcursesEnd()
{
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        delwin(win.second);
    });
    _windows.clear();
}

void NcursesEnd::display()
{
    erase();
    this->displayTitle();
    this->displayScoreUsername();
    this->displayBestScores();
    this->displayCommands();
}

void NcursesEnd::update()
{
}

void NcursesEnd::refresh()
{
    std::for_each(_windows.begin(), _windows.end(), [](const std::pair<std::string, WINDOW*>& win){
        wnoutrefresh(win.second);
    });
    ::refresh();
}

bool NcursesEnd::supportColor() const
{
    return _termColor;
}

void NcursesEnd::setGameStatsFormatString(const std::vector<std::pair<std::string, std::string>> &gameStats)
{
    _gameStats = gameStats;
}

void NcursesEnd::setScores(const std::vector<std::pair<std::string, std::string>> &scores)
{
    _bestScores = scores;
}

void NcursesEnd::displayTitle()
{
    delwin(_windows["Title"]);
    _windows["Title"] = subwin(stdscr, 15, 64, LINES / 8, COLS / 2 - 64 / 2);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Title"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["Title"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["Title"], 0, 0);
    mvwprintw(_windows["Title"], 2, 2, " .----------------.  .-----------------. .----------------.");
    mvwprintw(_windows["Title"], 3, 2, "| .--------------. || .--------------. || .--------------. |");
    mvwprintw(_windows["Title"], 4, 2, "| |  _________   | || | ____  _____  | || |  ________    | |");
    mvwprintw(_windows["Title"], 5, 2, "| | |_   ___  |  | || ||_   \\|_   _| | || | |_   ___ `.  | |");
    mvwprintw(_windows["Title"], 6, 2, "| |   | |_  \\_|  | || |  |   \\ | |   | || |   | |   `. \\ | |");
    mvwprintw(_windows["Title"], 7, 2, "| |   |  _|  _   | || |  | |\\ \\| |   | || |   | |    | | | |");
    mvwprintw(_windows["Title"], 8, 2, "| |  _| |___/ |  | || | _| |_\\   |_  | || |  _| |___.' / | |");
    mvwprintw(_windows["Title"], 9, 2, "| | |_________|  | || ||_____|\\____| | || | |________.'  | |");
    mvwprintw(_windows["Title"], 10, 2, "| |              | || |              | || |              | |");
    mvwprintw(_windows["Title"], 11, 2, "| '--------------' || '--------------' || '--------------' |");
    mvwprintw(_windows["Title"], 12, 2, "'----------------'  '----------------'  '----------------'");
    wattroff(_windows["Title"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesEnd::displayScoreUsername()
{
    int i = 0;
    delwin(_windows["UserInfos"]);
    _windows["UserInfos"] = subwin(stdscr, 20, 40, LINES / 2, COLS / 2 - 40 / 2);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["UserInfos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["UserInfos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["UserInfos"], 0, 0);
    mvwprintw(_windows["UserInfos"], 0, 0, "Your session");
    mvwprintw(_windows["UserInfos"], 2, 2, "Username : ");
    i = 3;
    if (_gameStats.has_value())
        for (const std::pair<std::string, std::string> &stat : *_gameStats) {
            mvwprintw(_windows["UserInfos"], i, 2, stat.first.c_str());
            mvwprintw(_windows["UserInfos"], i, 2 + stat.first.length(), " : ");
            i++;
        }
    wattroff(_windows["UserInfos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));

    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["UserInfos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    mvwprintw(_windows["UserInfos"], 2, 13, (_lib.getUsername().empty() ? "Unknown" : _lib.getUsername().c_str()));
    i = 3;
    if (_gameStats.has_value())
        for (const std::pair<std::string, std::string> &stat : *_gameStats) {
            mvwprintw(_windows["UserInfos"], i, 5 + stat.first.length(), stat.second.c_str());
            i++;
        }
    wattroff(_windows["UserInfos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesEnd::displayBestScores()
{
    delwin(_windows["BestScores"]);
    _windows["BestScores"] = subwin(stdscr, 14, 30, LINES / 4, COLS - 50);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["BestScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["BestScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["BestScores"], 0, 0);
    mvwprintw(_windows["BestScores"], 0, 0, "Best Scores on this game");
    wattroff(_windows["BestScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));

    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["BestScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    int i = 2;
    if (_bestScores.has_value() && !_bestScores->empty()) {
        for (const std::pair<std::string, std::string> &score : *_bestScores) {
            mvwprintw(_windows["BestScores"], i, 2, score.first.c_str());
            mvwprintw(_windows["BestScores"], i, score.first.length() + 2, ":");
            mvwprintw(_windows["BestScores"], i, score.first.length() + 4,
                      score.second.c_str());
            i++;
        }
    } else {
        mvwprintw(_windows["BestScores"], 2, 2, "No Best scores on this game");
    }
    wattroff(_windows["BestScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesEnd::displayCommands()
{
    delwin(_windows["Controls"]);
    _windows["Controls"] = subwin(stdscr, 30, 40, LINES / 4, 10);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Controls"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["Controls"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["Controls"], 0, 0);
    mvwprintw(_windows["Controls"], 0, 0, "Controls");
    wattroff(_windows["Controls"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));

    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Controls"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    int i = 2;
    if (_lib.getHowToPlay().has_value() && !_lib.getHowToPlay()->empty()) {
        for (const std::pair<std::string, std::string> &control : *_lib.getHowToPlay()) {
            mvwprintw(_windows["Controls"], i, 2, control.first.c_str());
            mvwprintw(_windows["Controls"], i, control.first.length() + 2, ":");
            mvwprintw(_windows["Controls"], i, control.first.length() + 4, control.second.c_str());
            i++;
        }
    } else {
        mvwprintw(_windows["Controls"], 2, 2, "No commands on this game");
    }
    wattroff(_windows["Controls"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}
