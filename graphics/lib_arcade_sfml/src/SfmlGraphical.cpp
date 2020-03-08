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

Event::Key SfmlGraphical::getKeyPressed() const
{
    return (_keyPressed);
}

void SfmlGraphical::setScene(Scene scene)
{
    _scene = scene;
}

SfmlGraphical::Scene SfmlGraphical::getScene() const
{
    return (_scene);
}

void SfmlGraphical::setSprites(const std::map<char, std::string> &sprites)
{
    _spriteMap = sprites;
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

Event::Type SfmlGraphical::getEventType()
{
    return (_eventType);
}

void SfmlGraphical::setScores(const std::vector<std::pair<std::string,std::string>> &scores)
{
    _scores = scores;
}

void SfmlGraphical::setFunctionPlay(const std::function<void()> &function)
{
}

void SfmlGraphical::setFunctionRestart(const std::function<void()> &function)
{
}

void SfmlGraphical::setFunctionMenu(const std::function<void()> &function)
{
}

void SfmlGraphical::setFunctionTogglePause(const std::function<void()> &function)
{
}

const std::string &SfmlGraphical::getUsername() const
{
    return (_username);
}

void SfmlGraphical::setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info)
{
}

void SfmlGraphical::setGameStatsFormatString(const std::vector<std::string> &info)
{
}

void SfmlGraphical::updateGameInfo(const std::vector<Entity> &gameMap)
{
}

void SfmlGraphical::setMusic(const std::string &music)
{
}

void SfmlGraphical::playSound(const std::string &sound)
{
}

void SfmlGraphical::setListGames(const std::vector<std::string>& games, const std::function<void (const std::string &)> &fct, int chosen)
{
}

void SfmlGraphical::setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen)
{
}

void SfmlGraphical::setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls)
{
}
