/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "SDLGraphical.hpp"
#include "SDLError.hpp"
#include "Scene/MainMenuScene.hpp"
#include "Scene/GameScene.hpp"
#include "Scene/GameOverScene.hpp"

using namespace arc;

extern "C" IGraphical *instance_ctor() {
    return (new SDLGraphical);
};

const std::map<SDL_Keycode, Event::Key> SDLGraphical::_equivalentKeys = {
    {SDLK_a, Event::A},
    {SDLK_b, Event::B},
    {SDLK_c, Event::C},
    {SDLK_d, Event::D},
    {SDLK_e, Event::E},
    {SDLK_f, Event::F},
    {SDLK_g, Event::G},
    {SDLK_h, Event::H},
    {SDLK_i, Event::I},
    {SDLK_j, Event::J},
    {SDLK_k, Event::K},
    {SDLK_l, Event::L},
    {SDLK_m, Event::M},
    {SDLK_n, Event::N},
    {SDLK_o, Event::O},
    {SDLK_p, Event::P},
    {SDLK_q, Event::Q},
    {SDLK_r, Event::R},
    {SDLK_s, Event::S},
    {SDLK_t, Event::T},
    {SDLK_u, Event::U},
    {SDLK_v, Event::V},
    {SDLK_w, Event::W},
    {SDLK_x, Event::X},
    {SDLK_y, Event::Y},
    {SDLK_z, Event::Z},
    {SDLK_PAUSE, Event::PAUSE},
    {SDLK_BACKSPACE, Event::BACKSPACE},
    {SDLK_TAB, Event::TAB},
    {SDLK_ESCAPE, Event::ESCAPE},
    {SDLK_DELETE, Event::DELETE},
    {SDLK_RETURN, Event::RETURN},
    {SDLK_UP, Event::UP},
    {SDLK_DOWN, Event::DOWN},
    {SDLK_LEFT, Event::LEFT},
    {SDLK_RIGHT, Event::RIGHT},
    {SDLK_INSERT, Event::INSERT},
    {SDLK_HOME, Event::HOME},
    {SDLK_END, Event::END},
    {SDLK_PAGEUP, Event::PAGEUP},
    {SDLK_PAGEDOWN, Event::PAGEDOWN},
    {SDLK_0, Event::NUM0},
    {SDLK_1, Event::NUM1},
    {SDLK_2, Event::NUM2},
    {SDLK_3, Event::NUM3},
    {SDLK_4, Event::NUM4},
    {SDLK_5, Event::NUM5},
    {SDLK_6, Event::NUM6},
    {SDLK_7, Event::NUM7},
    {SDLK_8, Event::NUM8},
    {SDLK_9, Event::NUM9},
    {SDLK_F1, Event::F1},
    {SDLK_F2, Event::F2},
    {SDLK_F3, Event::F3},
    {SDLK_F4, Event::F4},
    {SDLK_F5, Event::F5},
    {SDLK_F6, Event::F6},
    {SDLK_F7, Event::F7},
    {SDLK_F8, Event::F8},
    {SDLK_F9, Event::F9},
    {SDLK_F10, Event::F10},
    {SDLK_F11, Event::F11},
    {SDLK_F12, Event::F12},
};

SDLGraphical::SDLGraphical():
    _window(1600, 900, "Arcade"),
    _eventType(Event::NO_EVENT),
    _keyPressed(Event::NONE), _scene(MAIN_MENU), _font("assets/font.ttf")
{
    _window.setFramerateLimit(60);
    _scenes[MAIN_MENU] = std::make_unique<MainMenuScene>(_window, _font, *this);
    _scenes[GAME] = std::make_unique<GameScene>(_window, _font, *this);
    _scenes[END_GAME] = std::make_unique<GameOverScene>(_window, _font, *this);
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
            if (_equivalentKeys.count(_event.key.keysym.sym))
                _keyPressed = _equivalentKeys.at(_event.key.keysym.sym);
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
    static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setScores(scores);
}

void SDLGraphical::setFunctionPlay(const std::function<void()> &function)
{
    static_cast<MainMenuScene *>(_scenes.at(MAIN_MENU).get())->setFunctionPlay(function);
}

void SDLGraphical::setFunctionRestart(const std::function<void()> &function)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setFunctionRestart(function);
    static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setFunctionRestart(function);
}

void SDLGraphical::setFunctionMenu(const std::function<void()> &function)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setFunctionMenu(function);
    static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setFunctionMenu(function);
}

void SDLGraphical::setFunctionTogglePause(const std::function<void()> &fct)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setFunctionTogglePause(fct);
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
    static_cast<GameScene *>(_scenes.at(GAME).get())->setHowToPlay(info);
}

void SDLGraphical::setGameStats(const std::vector<std::pair<std::string, std::string>> &info)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setGameStats(info);
    static_cast<GameOverScene *>(_scenes.at(END_GAME).get())->setCurrentStats(
        static_cast<GameScene *>(_scenes.at(GAME).get())->getGameStats());
}

void SDLGraphical::updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->updateGameInfo(gameMap);
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
    static_cast<GameScene *>(_scenes.at(GAME).get())->setControls(controls);
}

void SDLGraphical::setMapSize(size_t height, size_t width)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setMapSize(height, width);
}

void SDLGraphical::setSpriteSize(MySDL::Sprite &sprite, const MySDL::Vector &size)
{
    sprite.setSize(size);
}

void SDLGraphical::setGameTitle(const std::string &game)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setGameTitle(game);
}

void SDLGraphical::setGamePause(bool pause)
{
    static_cast<GameScene *>(_scenes.at(GAME).get())->setPause(pause);
}
