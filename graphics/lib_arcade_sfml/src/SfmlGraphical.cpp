/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "SfmlGraphical.hpp"

using namespace arc;

SfmlGraphical::SfmlGraphical():
    _window(sf::VideoMode(1600, 900), "Arcade", sf::Style::Close),
    _gameMap(nullptr)
{
}

Event::Type SfmlGraphical::getEventType() const
{
    return (_eventType);
}

Event::Key SfmlGraphical::getKeyPressed() const
{
    return (_keyPressed);
}

size_t SfmlGraphical::getScreenHeight() const
{
    return (_window.getSize().y);
}

size_t SfmlGraphical::getScreenWidth() const
{
    return (_window.getSize().x);
}

void SfmlGraphical::setScene(Scene scene)
{
    _scene = scene;
}

SfmlGraphical::Scene SfmlGraphical::getScene() const
{
    return (_scene);
}

void SfmlGraphical::setMainMenuOptions(const std::map<std::string, std::function<void()>> &mainMenu)
{
    _mainMenuOptions = mainMenu;
}

void SfmlGraphical::setPauseMenuOptions(const std::map<std::string, std::function<void()>> &pauseMenu)
{
    _pauseMenuOptions = pauseMenu;
}

void SfmlGraphical::setList(const std::vector<std::string> &list)
{
    _list = list;
}

void SfmlGraphical::setGetInputMessage(const std::string &message)
{
    _getInputMessage = message;
}

void SfmlGraphical::setEndGameMessage(const std::string &message)
{
    _endGameMessage = message;
}

void SfmlGraphical::updateGameInfo(const std::vector<std::vector<char>> &gameMap)
{
    _gameMap = &gameMap;
}

const std::string &SfmlGraphical::getInput() const
{
    return (_input);
}
