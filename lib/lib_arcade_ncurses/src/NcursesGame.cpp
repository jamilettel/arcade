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
        _lib.addColor({7, 29, 27, 1});
        _lib.addColor({0, 0, 0, 1});
        _lib.initPairColor(_lib.getColor({0, 0, 0, 1}), _lib.getColor({7, 29, 27, 1}));
        wbkgd(stdscr, COLOR_PAIR(_lib.getPairColor(_lib.getColor({0, 0, 0, 1}), _lib.getColor({7, 29, 27, 1}))));
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
    this->displayUserName();
    this->displayMap();
    this->displayCommands();
    this->displayGameInfo();
    this->displayEntities();
    this->displayBestScore();
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
    std::pair<Event::Type, Event::Key> event;

    event.first = _lib.getEventType();
    event.second = _lib.getKeyPressed();
    if (_controlsFt.has_value() && _controlsFt->count(event))
        _controlsFt->at(event)();
}

void NcursesGame::setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()> > &controls)
{
    _controlsFt = controls;
}

void NcursesGame::setGameTitle(std::string gameTitle)
{
    _gameTitle = gameTitle;
}

void NcursesGame::displayTitleGame()
{
    delwin(_windows["Title"]);
    _windows["Title"] = subwin(stdscr, 5, 30, 2, COLS / 2 - 30 / 2);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Title"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["Title"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["Title"], 0, 0);
    mvwprintw(_windows["Title"], 2, 30 / 2 - _gameTitle.length() / 2, _gameTitle.c_str());
    wattroff(_windows["Title"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesGame::setMapSize(size_t height, size_t width)
{
    _mapSize.first = height;
    _mapSize.second = width;
}

void NcursesGame::displayMap()
{
    delwin(_windows["Map"]);
    _windows["Map"] = subwin(stdscr, _mapSize.first, _mapSize.second, LINES / 2 - _mapSize.first / 1.5, COLS / 2 - _mapSize.second / 2);
    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({234, 234, 234, 1}));
        wattron(_windows["Map"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({234, 234, 234, 1}))));
        wbkgd(_windows["Map"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({234, 234, 234, 1}))));
    }
    wbkgd(_windows["Map"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({234, 234, 234, 1}))));
    wattroff(_windows["Map"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({234, 234, 234, 1}))));
}

void NcursesGame::displayGameInfo()
{
    int i = 1;
    int j = 0;
    delwin(_windows["Infos"]);
    _windows["Infos"] = subwin(stdscr, 8, 90, LINES - 10, 10);

    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Infos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["Infos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["Infos"], 0, 0);
    mvwprintw(_windows["Infos"], 0, 0, "Game stats");
    wattroff(_windows["Infos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Infos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    if (_gameStats.has_value()) {
        for (const std::pair<std::string, std::string> &stat : *_gameStats) {
            if (i == 7) {
                j += 30;
                i = 1;
            }
            mvwprintw(_windows["Infos"], i, 1 + j, stat.first.c_str());
            mvwprintw(_windows["Infos"], i, 1 + j + stat.first.size(), " : ");
            mvwprintw(_windows["Infos"], i, 1 + j + stat.first.size() + 3, stat.second.c_str());
            i++;
        }
    }
    wattroff(_windows["Infos"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesGame::displayCommands()
{
    int i = 1;
    int j = 0;
    delwin(_windows["Commands"]);
    _windows["Commands"] = subwin(stdscr, 8, 90, LINES - 10, COLS - 100);

    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Commands"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["Commands"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["Commands"], 0, 0);
    mvwprintw(_windows["Commands"], 0, 0, "Commands");
    wattroff(_windows["Commands"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));

    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Commands"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    if (_controls.has_value()) {
        for (const std::pair<std::string, std::string> &control : *_controls) {
            if (i == 7) {
                j += 30;
                i = 1;
            }
            mvwprintw(_windows["Commands"], i, 1 + j, control.first.c_str());
            mvwprintw(_windows["Commands"], i, control.first.length() + 2 + j, ":");
            mvwprintw(_windows["Commands"], i, control.first.length() + 4 + j,
                      control.second.c_str());
            i++;
        }
    }
    wattroff(_windows["Commands"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}

void NcursesGame::displayEntities()
{
    if (!_entities.has_value())
        return;
    for (std::shared_ptr<Entity> &entitie : *_entities) {
        if (supportColor()) {
            _lib.addColor({entitie->backgroundColor.r, entitie->backgroundColor.g, entitie->backgroundColor.b, entitie->backgroundColor.a});
            _lib.initPairColor(_lib.getColor({entitie->backgroundColor.r, entitie->backgroundColor.g, entitie->backgroundColor.b, entitie->backgroundColor.a}), _lib.getColor({entitie->backgroundColor.r, entitie->backgroundColor.g, entitie->backgroundColor.b, entitie->backgroundColor.a}));
            wattron(_windows["Map"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({entitie->backgroundColor.r, entitie->backgroundColor.g, entitie->backgroundColor.b, entitie->backgroundColor.a}), _lib.getColor({entitie->backgroundColor.r, entitie->backgroundColor.g, entitie->backgroundColor.b, entitie->backgroundColor.a}))));
        }
        mvwprintw(_windows["Map"], entitie->y, entitie->x, " ");
        wattroff(_windows["Map"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({entitie->backgroundColor.r, entitie->backgroundColor.g, entitie->backgroundColor.b, entitie->backgroundColor.a}), _lib.getColor({entitie->backgroundColor.r, entitie->backgroundColor.g, entitie->backgroundColor.b, entitie->backgroundColor.a}))));
    }
}

void NcursesGame::updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap)
{
    _entities = gameMap;
}

void NcursesGame::setGameStatsFormatString(const std::vector<std::pair<std::string, std::string>> &gameStats)
{
    _gameStats = gameStats;
}

void NcursesGame::displayUserName()
{
    delwin(_windows["Username"]);
    _windows["Username"] = subwin(stdscr, 5, 30, 2, 20);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Username"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["Username"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["Username"], 0, 0);
    mvwprintw(_windows["Username"], 0, 0, "Username");
    wattroff(_windows["Username"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["Username"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    mvwprintw(_windows["Username"], 2, 30 / 2 - _lib.getUsername().length() / 2, _lib.getUsername().c_str());
    wattroff(_windows["Username"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));

}

void NcursesGame::displayBestScore()
{
    delwin(_windows["BScores"]);
    _windows["BScores"] = subwin(stdscr, 7, 60, 2, COLS - 70);
    if (supportColor()) {
        _lib.addColor({250, 233, 77, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["BScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
        wbkgd(_windows["BScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    box(_windows["BScores"], 0, 0);
    mvwprintw(_windows["BScores"], 0, 0, "Best Scores");
    wattroff(_windows["BScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({250, 233, 77, 1}), _lib.getColor({7, 29, 27, 1}))));
    if (supportColor()) {
        _lib.addColor({234, 234, 234, 1});
        _lib.addColor({7, 29, 27, 1});
        _lib.initPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}));
        wattron(_windows["BScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
    }
    wattroff(_windows["BScores"], COLOR_PAIR(_lib.getPairColor(_lib.getColor({234, 234, 234, 1}), _lib.getColor({7, 29, 27, 1}))));
}
