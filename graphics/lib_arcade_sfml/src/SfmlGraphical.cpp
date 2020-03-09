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
    _window(sf::VideoMode(1600, 900), "Arcade"), _mapHeight(0), _mapWidth(0)
{
    _window.setFramerateLimit(60);
}

void SfmlGraphical::display()
{
    checkEvents();
    if (getScene() == Scene::MAIN_MENU) {
        std::for_each(_mainMenuButtons.begin(), _mainMenuButtons.end(),
                      [] (auto &button) {button->draw();});
        std::for_each(_gamesList.begin(), _gamesList.end(),
                      [] (auto &button) {button->draw();});
    }
    _window.display();
    _window.clear();
}

void SfmlGraphical::checkEvents()
{
    _eventType = Event::NO_EVENT;
    _keyPressed = Event::NONE;

    if (!_window.isOpen()) {
        _eventType = Event::QUIT;
        return;
    }
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window.close();
            _eventType = Event::QUIT;
        }
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
    _mainMenuButtons.erase(_mainMenuButtons.begin(), _mainMenuButtons.end());
    _mainMenuButtons.push_back(
        std::unique_ptr<MySf::Button::RectButton>(
            new MySf::Button::RectButton(_window,
                                         sf::Vector2f(100, 100),
                                         sf::Vector2f(200, 50),
                                         _font,
                                         BUTTON_COLOR,
                                         TEXT_COLOR,
                                         "Play",
                                         function)));
    _mainMenuButtons.push_back(
        std::unique_ptr<MySf::Button::RectButton>(
            new MySf::Button::RectButton(_window,
                                         sf::Vector2f(100, 175),
                                         sf::Vector2f(200, 50),
                                         _font,
                                         BUTTON_COLOR,
                                         TEXT_COLOR,
                                         "Exit",
                                         [this] () {
                                             _window.close();
                                         })));
}

void SfmlGraphical::setFunctionRestart(const std::function<void()> &function)
{
    _pauseMenuButtons.push_back(
        std::unique_ptr<MySf::Button::RectButton>(
            new MySf::Button::RectButton(_window,
                                         sf::Vector2f(100, 175),
                                         sf::Vector2f(200, 50),
                                         _font,
                                         BUTTON_COLOR,
                                         TEXT_COLOR,
                                         "Restart",
                                         function)));
}

void SfmlGraphical::setFunctionMenu(const std::function<void()> &function)
{
    _pauseMenuButtons.push_back(
        std::unique_ptr<MySf::Button::RectButton>(
            new MySf::Button::RectButton(_window,
                                         sf::Vector2f(100, 250),
                                         sf::Vector2f(200, 50),
                                         _font,
                                         BUTTON_COLOR,
                                         TEXT_COLOR,
                                         "Return to menu",
                                         function)));
}

void SfmlGraphical::setFunctionTogglePause(const std::function<void()> &function)
{
    _pauseMenuButtons.push_back(
        std::unique_ptr<MySf::Button::RectButton>(
            new MySf::Button::RectButton(_window,
                                         sf::Vector2f(100, 100),
                                         sf::Vector2f(200, 50),
                                         _font,
                                         BUTTON_COLOR,
                                         TEXT_COLOR,
                                         "Resume",
                                         function)));

    _pauseButton = std::unique_ptr<MySf::Button::RectButton>(
        new MySf::Button::RectButton(_window,
                                     sf::Vector2f(100, 100),
                                     sf::Vector2f(200, 50),
                                     _font,
                                     BUTTON_COLOR,
                                     TEXT_COLOR,
                                     "Pause",
                                     function));
}

const std::string &SfmlGraphical::getUsername() const
{
    return (_username);
}

void SfmlGraphical::setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info)
{
    _controls = info;
}

void SfmlGraphical::setGameStatsFormatString(const std::vector<std::string> &info)
{
    _gameStats = info;
}

void SfmlGraphical::updateGameInfo(const std::vector<Entity> &gameMap)
{
    _gameMap = gameMap;
}

void SfmlGraphical::setMusic(const std::string &music)
{
    if (_music.openFromFile(music)) {
        _music.setLoop(true);
        _music.play();
    }
}

void SfmlGraphical::playSound(const std::string &)
{
}

void SfmlGraphical::setListGames(const std::vector<std::string> &games,
                                 const std::function<void (const std::string &)> &fct,
                                 int)
{
    sf::Vector2f pos(600, 100);

    _changeGameFct = fct;
    std::for_each(games.begin(), games.end(),
                  [&pos, this] (const std::string &game) {
                      _gamesList.push_back(
                          std::unique_ptr<MySf::Button::IButton>(
                              new MySf::Button::RectButton(_window,
                                                           pos,
                                                           sf::Vector2f(700, 50),
                                                           _font,
                                                           BUTTON_COLOR,
                                                           TEXT_COLOR,
                                                           game,
                                                           [this, game] () {
                                                               _changeGameFct(game);
                                                           })));
                      pos.y += 50;
                  });
}

void SfmlGraphical::setListLibraries(const std::vector<std::string> &libraries,
                                     const std::function<void (const std::string &)> &fct,
                                     int chosen)
{
}

void SfmlGraphical::setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls)
{
    _controlsMap = controls;
}

void SfmlGraphical::setMapSize(size_t height, size_t width)
{
    _mapHeight = height;
    _mapWidth = width;
}
