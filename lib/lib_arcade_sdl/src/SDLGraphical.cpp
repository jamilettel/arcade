/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "SDLGraphical.hpp"
#include "SDLError.hpp"
#include "Scene/MainMenuScene.hpp"
// #include "Scene/GameScene.hpp"
// #include "Scene/GameOverScene.hpp"

using namespace arc;

extern "C" IGraphical *instance_ctor() {
    return (new SDLGraphical);
};

const std::map<SDL_Scancode, Event::Key> SDLGraphical::_equivalentKeys = {
    {SDL_SCANCODE_A, Event::A},
    {SDL_SCANCODE_B, Event::B},
    {SDL_SCANCODE_C, Event::C},
    {SDL_SCANCODE_D, Event::D},
    {SDL_SCANCODE_E, Event::E},
    {SDL_SCANCODE_F, Event::F},
    {SDL_SCANCODE_G, Event::G},
    {SDL_SCANCODE_H, Event::H},
    {SDL_SCANCODE_I, Event::I},
    {SDL_SCANCODE_J, Event::J},
    {SDL_SCANCODE_K, Event::K},
    {SDL_SCANCODE_L, Event::L},
    {SDL_SCANCODE_M, Event::M},
    {SDL_SCANCODE_N, Event::N},
    {SDL_SCANCODE_O, Event::O},
    {SDL_SCANCODE_P, Event::P},
    {SDL_SCANCODE_Q, Event::Q},
    {SDL_SCANCODE_R, Event::R},
    {SDL_SCANCODE_S, Event::S},
    {SDL_SCANCODE_T, Event::T},
    {SDL_SCANCODE_U, Event::U},
    {SDL_SCANCODE_V, Event::V},
    {SDL_SCANCODE_W, Event::W},
    {SDL_SCANCODE_X, Event::X},
    {SDL_SCANCODE_Y, Event::Y},
    {SDL_SCANCODE_Z, Event::Z},
    {SDL_SCANCODE_PAUSE, Event::PAUSE},
    {SDL_SCANCODE_BACKSPACE, Event::BACKSPACE},
    {SDL_SCANCODE_TAB, Event::TAB},
    {SDL_SCANCODE_ESCAPE, Event::ESCAPE},
    {SDL_SCANCODE_DELETE, Event::DELETE},
    {SDL_SCANCODE_RETURN, Event::RETURN},
    {SDL_SCANCODE_UP, Event::UP},
    {SDL_SCANCODE_DOWN, Event::DOWN},
    {SDL_SCANCODE_LEFT, Event::LEFT},
    {SDL_SCANCODE_RIGHT, Event::RIGHT},
    {SDL_SCANCODE_INSERT, Event::INSERT},
    {SDL_SCANCODE_HOME, Event::HOME},
    {SDL_SCANCODE_END, Event::END},
    {SDL_SCANCODE_PAGEUP, Event::PAGEUP},
    {SDL_SCANCODE_PAGEDOWN, Event::PAGEDOWN},
    {SDL_SCANCODE_0, Event::NUM0},
    {SDL_SCANCODE_1, Event::NUM1},
    {SDL_SCANCODE_2, Event::NUM2},
    {SDL_SCANCODE_3, Event::NUM3},
    {SDL_SCANCODE_4, Event::NUM4},
    {SDL_SCANCODE_5, Event::NUM5},
    {SDL_SCANCODE_6, Event::NUM6},
    {SDL_SCANCODE_7, Event::NUM7},
    {SDL_SCANCODE_8, Event::NUM8},
    {SDL_SCANCODE_9, Event::NUM9},
    {SDL_SCANCODE_F1, Event::F1},
    {SDL_SCANCODE_F2, Event::F2},
    {SDL_SCANCODE_F3, Event::F3},
    {SDL_SCANCODE_F4, Event::F4},
    {SDL_SCANCODE_F5, Event::F5},
    {SDL_SCANCODE_F6, Event::F6},
    {SDL_SCANCODE_F7, Event::F7},
    {SDL_SCANCODE_F8, Event::F8},
    {SDL_SCANCODE_F9, Event::F9},
    {SDL_SCANCODE_F10, Event::F10},
    {SDL_SCANCODE_F11, Event::F11},
    {SDL_SCANCODE_F12, Event::F12},
};

SDLGraphical::SDLGraphical():
    _window(1600, 900, "Arcade"),
    _eventType(Event::NO_EVENT),
    _keyPressed(Event::NONE), _scene(MAIN_MENU), _font("assets/font.ttf")
{
    _window.setFramerateLimit(60);
    _scenes[MAIN_MENU] = std::make_unique<MainMenuScene>(_window, _font, *this);
    // _scenes[GAME] = std::make_unique<GameScene>(_window, _font, *this);
    // _scenes[END_GAME] = std::make_unique<GameOverScene>(_window, _font, *this);
}

void SDLGraphical::display()
{
    checkEvents();
    if (_scenes.count(_scene))
        _scenes.at(_scene)->draw();
    _window.display();
    _window.clear(SDL_Color{0x1c, 0x1c, 0x1c, 0xff});
}

void SDLGraphical::loadSprite(const std::string &spritePath, const Color &color)
{
    if (spritePath.substr(0, 7) == "__color") {
        _sprites[spritePath].setColor({color.r, color.g, color.b, color.a});
        return;
    }
    try {
        _sprites[spritePath].loadFile(spritePath, _window);
    } catch (SDLError &e) {
        _sprites[spritePath].setColor({color.r, color.g, color.b, color.a});
    }
}

MySDL::Sprite &SDLGraphical::getSprite(const std::string &sprite,
                                       const MySDL::Vector &size,
                                       const Color &color)
{
    if (sprite == "") {
        Uint32 c = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
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

void SDLGraphical::checkEvents()
{
    static std::pair<Event::Type, Event::Key> event;
    _eventType = Event::NO_EVENT;
    _keyPressed = Event::NONE;

    if (!_window.isOpen()) {
        _eventType = Event::QUIT;
        return;
    }
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            _window.close();
            _eventType = Event::QUIT;
        } else if (_event.type == SDL_KEYDOWN ||
                   _event.type == SDL_KEYUP) {
            if (_event.type == SDL_KEYDOWN)
                _eventType = Event::KEY_PRESSED;
            else
                _eventType = Event::KEY_RELEASED;
            if (_equivalentKeys.count(_event.key.keysym.scancode))
                _keyPressed = _equivalentKeys.at(_event.key.keysym.scancode);
            else
                _keyPressed = Event::Key::NONE;
        } else if (_event.type == SDL_MOUSEBUTTONDOWN) {
            _eventType = Event::MOUSE_PRESSED;
            switch (_event.button.button) {
            case (SDL_BUTTON_LEFT):
                _keyPressed = Event::MOUSE_1;
                break;
            case (SDL_BUTTON_MIDDLE):
                _keyPressed = Event::MOUSE_2;
                break;
            case (SDL_BUTTON_RIGHT):
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

Event::Key SDLGraphical::getKeyPressed() const
{
    return (_keyPressed);
}

void SDLGraphical::setScene(Scene scene)
{
    _scene = scene;
}

SDLGraphical::Scene SDLGraphical::getScene() const
{
    return (_scene);
}

Event::Type SDLGraphical::getEventType() const
{
    return (_eventType);
}

void SDLGraphical::setScores(const std::vector<std::pair<std::string,std::string>> &scores)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setScores(scores);
    // static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setScores(scores);
}

void SDLGraphical::setFunctionPlay(const std::function<void()> &function)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setFunctionPlay(function);
}

void SDLGraphical::setFunctionRestart(const std::function<void()> &function)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setFunctionRestart(function);
    // static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setFunctionRestart(function);
}

void SDLGraphical::setFunctionMenu(const std::function<void()> &function)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setFunctionMenu(function);
    // static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setFunctionMenu(function);
}

void SDLGraphical::setFunctionTogglePause(const std::function<void()> &fct)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setFunctionTogglePause(fct);
}

const std::string &SDLGraphical::getUsername()
{
    return (static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->getUsername());
}

void SDLGraphical::setUsername(const std::string &name)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setUsername(name);
}

void SDLGraphical::setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setHowToPlay(info);
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setHowToPlay(info);
}

void SDLGraphical::setGameStats(const std::vector<std::pair<std::string, std::string>> &info)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setGameStats(info);
    // static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setCurrentStats(
    //     static_cast<GameScene *>(_scenes.at(GAME).get())->getGameStats());
}

void SDLGraphical::updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->updateGameInfo(gameMap);
}

void SDLGraphical::setListGames(const std::vector<std::string> &games,
                                 const std::function<void (const std::string &)> &fct,
                                 int chosen)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setListGames(games, fct, chosen);
}

void SDLGraphical::setListLibraries(const std::vector<std::string> &libraries,
                                     const std::function<void (const std::string &)> &fct,
                                     int chosen)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setListLibraries(libraries, fct, chosen);
}

void SDLGraphical::setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setControls(controls);
}

void SDLGraphical::setMapSize(size_t height, size_t width)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setMapSize(height, width);
}

void SDLGraphical::setSpriteSize(MySDL::Sprite &sprite, const MySDL::Vector &size)
{
    sprite.setSize(size);
}

void SDLGraphical::setGameTitle(const std::string &game)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setGameTitle(game);
}

void SDLGraphical::setGamePause(bool pause)
{
    // static_cast<GameScene *>(_scenes.at(GAME).get())->setPause(pause);
}
