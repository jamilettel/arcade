/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "SfmlGraphical.hpp"
#include "SfmlError.hpp"

using namespace arc;

extern "C" IGraphical *instance_ctor() {
    return (new SfmlGraphical);
};

SfmlGraphical::SfmlGraphical():
    _window(sf::VideoMode(1600, 900), "Arcade", sf::Style::Close, sf::ContextSettings(0, 0, 8)),
    _gameMap(nullptr)
{
    _window.setFramerateLimit(60);
}

void SfmlGraphical::display()
{
    checkEvents();
    _window.display();
}

void SfmlGraphical::checkEvents()
{
    _eventType = Event::NO_EVENT;
    _keyPressed = Event::NONE;

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _eventType = Event::QUIT;
    }
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

void SfmlGraphical::setSprites(const std::map<char, std::string> &sprites)
{
    std::for_each(sprites.begin(), sprites.end(),
                  [this] (const std::pair<char, std::string> &it) {
                      if (!_textures[it.first].loadFromFile(it.second))
                          throw SfmlError("could not load texture '" + it.second + "'");
                      _sprites[it.first].setTexture(_textures[it.first]);
                  });
}

void SfmlGraphical::setBackgroundColors(const std::map<char, Color> &)
{
    // left empty intentionnaly: will not be used in SFML
}

void SfmlGraphical::setFont(const std::string &font)
{
    if (!_font.loadFromFile(font))
        throw SfmlError("could not load font '" + font + "'");
    _text.setFont(_font);
}

void SfmlGraphical::setGameStatsFormatString(const std::string &info)
{
    _gameStats = info;
}

void SfmlGraphical::setHowToPlayFormatString(const std::string &info)
{
    _howToPlay = info;
}
