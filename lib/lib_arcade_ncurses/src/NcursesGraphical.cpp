/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "NcursesError.hpp"
#include "NcursesGraphical.hpp"

using namespace arc;

extern "C" IGraphical *instance_ctor() {
    return (new NcursesGraphical);
}

NcursesGraphical::NcursesGraphical()
{
    initscr();
    printw("Hello World");
    refresh();
}

NcursesGraphical::~NcursesGraphical()
{
    endwin();
}

void NcursesGraphical::display()
{
    switch (getScene()) {
        case (Scene::MAIN_MENU):
            getch();
            _eventType = Event::QUIT;
            break;
        default:
            break;
    }
}

Event::Type NcursesGraphical::getEventType() const
{
    return _eventType;
}

Event::Key NcursesGraphical::getKeyPressed() const
{
    return _keyPressed;
}

void NcursesGraphical::setScores(const std::vector<std::pair<std::string, std::string> > &scores)
{
    _scores = scores;
}

void NcursesGraphical::setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()> > &controls)
{
    _controlsMap.emplace(controls);
}

const std::string & NcursesGraphical::getUsername() const
{
    return _username;
}

void NcursesGraphical::setScene(Scene scene)
{
    _scene = scene;
}

IGraphical::Scene NcursesGraphical::getScene() const
{
    return _scene;
}

void NcursesGraphical::setGameTitle(const std::string &game)
{
    _gameTitle = game;
}

void NcursesGraphical::setListGames(const std::vector<std::string> &games, const std::function<void(const std::string &)> &fct, int chosen)
{

}

void NcursesGraphical::setListLibraries(const std::vector<std::string> &libraries, const std::function<void(const std::string &)> &fct, int chosen)
{

}

void NcursesGraphical::setFunctionPlay(const std::function<void()> &function)
{

}

void NcursesGraphical::setFunctionMenu(const std::function<void()> &function)
{

}

void NcursesGraphical::setFunctionTogglePause(const std::function<void()> &function)
{

}

void NcursesGraphical::setFunctionRestart(const std::function<void()> &function)
{

}

void NcursesGraphical::setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info)
{

}

void NcursesGraphical::setGameStatsFormatString(const std::vector<std::string> &info)
{

}

void NcursesGraphical::setFont(const std::string &font)
{

}

void NcursesGraphical::setVisualAssets(const std::map<char, std::pair<std::string, Color> > &sprites)
{

}

void NcursesGraphical::updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap)
{

}

void NcursesGraphical::setMusic(const std::string &music)
{

}

void NcursesGraphical::playSound(const std::string &sound)
{

}

void NcursesGraphical::setMapSize(size_t height, size_t width)
{

}
