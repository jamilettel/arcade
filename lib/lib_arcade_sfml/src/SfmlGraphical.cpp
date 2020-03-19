
/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "SfmlGraphical.hpp"
#include "SfmlError.hpp"
#include "Scene/MainMenuScene.hpp"
#include "Scene/GameScene.hpp"

using namespace arc;

extern "C" IGraphical *instance_ctor() {
    return (new SfmlGraphical);
};

const std::map<sf::Keyboard::Key, Event::Key> SfmlGraphical::_equivalentKeys = {
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
    {sf::Keyboard::Pause, Event::PAUSE},
    {sf::Keyboard::BackSpace, Event::BACKSPACE},
    {sf::Keyboard::Tab, Event::TAB},
    {sf::Keyboard::Escape, Event::ESCAPE},
    {sf::Keyboard::Delete, Event::DELETE},
    {sf::Keyboard::Return, Event::RETURN},
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
    _window(sf::VideoMode(1600, 900), "Arcade", sf::Style::Close), _eventType(Event::NO_EVENT),
    _keyPressed(Event::NONE), _scene(MAIN_MENU)
{
    _window.setFramerateLimit(60);
    _scenes[MAIN_MENU] = std::make_unique<MainMenuScene>(_window, _font, *this);
    _scenes[GAME] = std::make_unique<GameScene>(_window, _font, *this);
}

void SfmlGraphical::display()
{
    checkEvents();
    if (_scenes.count(_scene))
        _scenes.at(_scene)->draw();
    _window.display();
    _window.clear(sf::Color(0x1c1c1cff));
}

void SfmlGraphical::loadSprite(const std::string &spritePath, const Color &color)
{
    if (spritePath.substr(0, 7) == "__color" || !_textures[spritePath].loadFromFile(spritePath)) {
        sf::Color sfmlColor(color.r, color.g, color.b, color.a);
        static sf::Uint32 pixel = 0xffffffff;

        _textures[spritePath].create(1, 1);
        _textures[spritePath].update(reinterpret_cast<sf::Uint8 *>(&pixel));
        _sprites[spritePath].setTexture(_textures[spritePath]);
        _sprites[spritePath].setColor(sfmlColor);
    } else
        _sprites[spritePath].setTexture(_textures[spritePath]);
}

sf::Sprite &SfmlGraphical::getSprite(const std::string &sprite,
                                     const sf::Vector2f &size,
                                     const Color &color)
{
    if (sprite == "") {
        sf::Uint32 c = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
        std::string spriteName = "__color" + std::to_string(c);

        return (getSprite(spriteName, size, color));
    }
    if (_sprites.count(sprite)) {
        setSpriteSize(_sprites.at(sprite), size);
        return (_sprites.at(sprite));
    }
    loadSprite(sprite, color);
    return (getSprite(sprite, size, color));
}

void SfmlGraphical::checkEvents()
{
    static std::pair<Event::Type, Event::Key> event;
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
        } else if (_event.type == sf::Event::KeyPressed ||
                   _event.type == sf::Event::KeyReleased) {
            if (_event.type == sf::Event::KeyPressed)
                _eventType = Event::KEY_PRESSED;
            else
                _eventType = Event::KEY_RELEASED;
            if (_equivalentKeys.count(_event.key.code))
                _keyPressed = _equivalentKeys.at(_event.key.code);
            else
                _keyPressed = Event::Key::NONE;
        } else if (_event.type == sf::Event::MouseButtonPressed) {
            _eventType = Event::MOUSE_PRESSED;
            switch (_event.mouseButton.button) {
            case (sf::Mouse::Button::Left):
                _keyPressed = Event::MOUSE_1;
                break;
            case (sf::Mouse::Button::Middle):
                _keyPressed = Event::MOUSE_2;
                break;
            case (sf::Mouse::Button::Right):
                _keyPressed = Event::MOUSE_3;
                break;
            default:
                _keyPressed = Event::NONE;
                break;
            }
        }

        if (_scenes.count(_scene))
            _scenes.at(_scene)->update(_event);

        event.first = _eventType;
        event.second = _keyPressed;
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

void SfmlGraphical::setFont(const std::string &font)
{
    sf::FloatRect gameTitleBounds;

    if (!_font.loadFromFile(font))
        throw SfmlError("could not load font '" + font + "'");
}

Event::Type SfmlGraphical::getEventType() const
{
    return (_eventType);
}

void SfmlGraphical::setScores(const std::vector<std::pair<std::string,std::string>> &scores)
{
}

void SfmlGraphical::setFunctionPlay(const std::function<void()> &function)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setFunctionPlay(function);
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

const std::string &SfmlGraphical::getUsername()
{
    return (static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->getUsername());
}

void SfmlGraphical::setUsername(const std::string &name)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setUsername(name);
}

void SfmlGraphical::setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info)
{
}

void SfmlGraphical::setGameStats(const std::vector<std::pair<std::string, std::string>> &info)
{
}

void SfmlGraphical::updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->updateGameInfo(gameMap);
}

void SfmlGraphical::setListGames(const std::vector<std::string> &games,
                                 const std::function<void (const std::string &)> &fct,
                                 int chosen)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setListGames(games, fct, chosen);
}

void SfmlGraphical::setListLibraries(const std::vector<std::string> &libraries,
                                     const std::function<void (const std::string &)> &fct,
                                     int chosen)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setListLibraries(libraries, fct, chosen);
}

void SfmlGraphical::setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setControls(controls);
}

void SfmlGraphical::setMapSize(size_t height, size_t width)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setMapSize(height, width);
}

void SfmlGraphical::setSpriteSize(sf::Sprite &sprite, const sf::Vector2f &size)
{
    sf::FloatRect rect = sprite.getGlobalBounds();
    sf::Vector2f scale;

    if (!rect.width || !rect.height || (rect.height == size.x && rect.width == size.y))
        return;
    scale.x = size.x / rect.width;
    scale.y = size.y / rect.height;
    sprite.scale(scale);
}

void SfmlGraphical::setGameTitle(const std::string &game)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setGameTitle(game);
}
