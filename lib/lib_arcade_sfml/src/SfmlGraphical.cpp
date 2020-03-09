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

const std::map<sf::Keyboard::Key, Event::Key> equivalentKeys = {
    {sf::Keyboard::A, Event::A},
    {sf::Keyboard::B, Event::B},
    {sf::Keyboard::C, Event::C},
    {sf::Keyboard::D, Event::D},
    {sf::Keyboard::E, Event::E},
    {sf::Keyboard::F, Event::F},
    {sf::Keyboard::G, Event::G},
    {sf::Keyboard::H, Event::H},
    {sf::Keyboard::I, Event::I},
    {sf::Keyboard::J, Event::J},
    {sf::Keyboard::K, Event::K},
    {sf::Keyboard::L, Event::L},
    {sf::Keyboard::M, Event::M},
    {sf::Keyboard::N, Event::N},
    {sf::Keyboard::Q, Event::Q},
    {sf::Keyboard::R, Event::R},
    {sf::Keyboard::S, Event::S},
    {sf::Keyboard::T, Event::T},
    {sf::Keyboard::U, Event::U},
    {sf::Keyboard::V, Event::V},
    {sf::Keyboard::W, Event::W},
    {sf::Keyboard::X, Event::X},
    {sf::Keyboard::Y, Event::Y},
    {sf::Keyboard::Z, Event::Z},
    {sf::Keyboard::Enter, Event::RETURN},
    {sf::Keyboard::Pause, Event::PAUSE},
    {sf::Keyboard::BackSpace, Event::BACKSPACE},
    {sf::Keyboard::Tab, Event::TAB},
    {sf::Keyboard::Escape, Event::ESCAPE},
    {sf::Keyboard::Delete, Event::DELETE},
    {sf::Keyboard::Up, Event::UP},
    {sf::Keyboard::Down, Event::DOWN},
    {sf::Keyboard::Left, Event::LEFT},
    {sf::Keyboard::Right, Event::RIGHT},
    {sf::Keyboard::Insert, Event::INSERT},
    {sf::Keyboard::Home, Event::HOME},
    {sf::Keyboard::End, Event::END},
    {sf::Keyboard::PageUp, Event::PAGEUP},
    {sf::Keyboard::PageDown, Event::PAGEDOWN},
    {sf::Keyboard::Num0, Event::NUM0},
    {sf::Keyboard::Num1, Event::NUM1},
    {sf::Keyboard::Num2, Event::NUM2},
    {sf::Keyboard::Num3, Event::NUM3},
    {sf::Keyboard::Num4, Event::NUM4},
    {sf::Keyboard::Num5, Event::NUM5},
    {sf::Keyboard::Num6, Event::NUM6},
    {sf::Keyboard::Num7, Event::NUM7},
    {sf::Keyboard::Num8, Event::NUM8},
    {sf::Keyboard::Num9, Event::NUM9},
    {sf::Keyboard::F1, Event::F1},
    {sf::Keyboard::F2, Event::F2},
    {sf::Keyboard::F3, Event::F3},
    {sf::Keyboard::F4, Event::F4},
    {sf::Keyboard::F5, Event::F5},
    {sf::Keyboard::F6, Event::F6},
    {sf::Keyboard::F7, Event::F7},
    {sf::Keyboard::F8, Event::F8},
    {sf::Keyboard::F9, Event::F9},
    {sf::Keyboard::F10, Event::F10},
    {sf::Keyboard::F11, Event::F11},
    {sf::Keyboard::F12, Event::F12},
};

SfmlGraphical::SfmlGraphical():
    _window(sf::VideoMode(1600, 900), "Arcade"), _mapHeight(0), _mapWidth(0), _controlsMap(nullptr)
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
    _controlsMap = &controls;
}

void SfmlGraphical::setMapSize(size_t height, size_t width)
{
    _mapHeight = height;
    _mapWidth = width;
}