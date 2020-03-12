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

}

NcursesGraphical::~NcursesGraphical()
{

}

void NcursesGraphical::display()
{

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