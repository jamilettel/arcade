/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "NcursesError.hpp"
#include "NcursesGraphical.hpp"
#include "NcursesMainMenu.hpp"
#include "NcursesGame.hpp"

using namespace arc;

extern "C" IGraphical *instance_ctor() {
    return (new NcursesGraphical);
}

const std::map<int, Event::Key> NcursesGraphical::_equivalentKeys = {
    {97, Event::Key::A},
    {98, Event::Key::B},
    {99, Event::Key::C},
    {100, Event::Key::D},
    {101, Event::Key::E},
    {102, Event::Key::F},
    {103, Event::Key::G},
    {104, Event::Key::H},
    {105, Event::Key::I},
    {106, Event::Key::J},
    {107, Event::Key::K},
    {108, Event::Key::L},
    {109, Event::Key::M},
    {110, Event::Key::N},
    {111, Event::Key::O},
    {112, Event::Key::P},
    {113, Event::Key::Q},
    {114, Event::Key::R},
    {115, Event::Key::S},
    {116, Event::Key::T},
    {117, Event::Key::U},
    {118, Event::Key::V},
    {119, Event::Key::W},
    {120, Event::Key::X},
    {121, Event::Key::Y},
    {122, Event::Key::Z},
    {KEY_BACKSPACE, Event::Key::BACKSPACE},
    {9, Event::Key::TAB},
    {10, Event::Key::ENTER},
    {27, Event::Key::ESCAPE},
    {330, Event::Key::DELETE},
    {KEY_UP, Event::Key::UP},
    {KEY_DOWN, Event::Key::DOWN},
    {KEY_LEFT, Event::Key::LEFT},
    {KEY_RIGHT, Event::Key::RIGHT},
    {331, Event::Key::INSERT},
    {48, Event::Key::NUM0},
    {49, Event::Key::NUM1},
    {50, Event::Key::NUM2},
    {51, Event::Key::NUM3},
    {52, Event::Key::NUM4},
    {53, Event::Key::NUM5},
    {54, Event::Key::NUM6},
    {55, Event::Key::NUM7},
    {56, Event::Key::NUM8},
    {57, Event::Key::NUM9},
    {KEY_F(1), Event::Key::F1},
    {KEY_F(2), Event::Key::F2},
    {KEY_F(3), Event::Key::F3},
    {KEY_F(4), Event::Key::F4},
    {KEY_F(5), Event::Key::F5},
    {KEY_F(6), Event::Key::F6},
    {KEY_F(7), Event::Key::F7},
    {KEY_F(8), Event::Key::F8},
    {KEY_F(9), Event::Key::F9},
    {KEY_F(10), Event::Key::F10},
    {KEY_F(11), Event::Key::F11},
    {KEY_F(12), Event::Key::F12},
};

NcursesGraphical::NcursesGraphical() : _eventType(Event::NO_EVENT), _keyPressed(Event::NONE), _scene(MAIN_MENU)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    _termColor = has_colors();
    if (supportColor())
        start_color();
    _sceneList[MAIN_MENU] = std::shared_ptr<IScene>(new NcursesMainMenu(*this));
    _sceneList[GAME] = std::shared_ptr<IScene>(new NcursesGame(*this));
}

NcursesGraphical::~NcursesGraphical()
{
    echo();
    nocbreak();
    endwin();
}

void NcursesGraphical::display()
{
    if (LINES < 50 || COLS < 150) {
        erase();
        mvprintw((LINES / 2), (COLS / 2) - (21 / 2), "window size too small");
        refresh();
    } else {
        checkEvents();
        _sceneList[getScene()]->display();
        _sceneList[getScene()]->refresh();
    }
}

void NcursesGraphical::checkEvents()
{
    int key_pressed;
    _keyPressed = Event::NONE;
    _eventType = Event::NO_EVENT;
    key_pressed = getch();
    if (_equivalentKeys.count(key_pressed)) {
        _keyPressed = _equivalentKeys.at(key_pressed);
        _eventType = Event::Type::KEY_PRESSED;
    }
    if (_sceneList.count(_scene))
        _sceneList.at(_scene)->update();
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
    static_cast<NcursesGame *>(_sceneList.at(GAME).get())->setControls(controls);
}

const std::string & NcursesGraphical::getUsername()
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
    dynamic_cast<NcursesGame *>(_sceneList[GAME].get())->setGameTitle(game);
}

void NcursesGraphical::setListGames(const std::vector<std::string> &games, const std::function<void(const std::string &)> &fct, int chosen)
{
    dynamic_cast<NcursesMainMenu *>(_sceneList[MAIN_MENU].get())->setListGames(games, fct, chosen);
}

void NcursesGraphical::setListLibraries(const std::vector<std::string> &libraries, const std::function<void(const std::string &)> &fct, int chosen)
{
    dynamic_cast<NcursesMainMenu *>(_sceneList[MAIN_MENU].get())->setListGraphics(libraries, fct, chosen);
}

void NcursesGraphical::setFunctionPlay(const std::function<void()> &function)
{
    _playFct = function;
}

void NcursesGraphical::setFunctionMenu(const std::function<void()> &function)
{
    _menuFct = function;
}

void NcursesGraphical::setFunctionTogglePause(const std::function<void()> &function)
{
    _pauseFct = function;
}

void NcursesGraphical::setFunctionRestart(const std::function<void()> &function)
{
    _restartFct = function;
}

void NcursesGraphical::setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info)
{
    _controlsString = info;
}

std::optional<std::vector<std::pair<std::string, std::string>>>& NcursesGraphical::getHowToPlay()
{
    return _controlsString;
}

void NcursesGraphical::setGameStatsFormatString(const std::vector<std::string> &info)
{
    dynamic_cast<NcursesGame *>(_sceneList[GAME].get())->setGameStatsFormatString(info);
}

void NcursesGraphical::setFont(const std::string &font)
{
    (void)font;
}

void NcursesGraphical::setVisualAssets(const std::map<char, std::pair<std::string, Color> > &sprites)
{

}

void NcursesGraphical::updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap)
{
    dynamic_cast<NcursesGame *>(_sceneList[GAME].get())->updateGameInfo(gameMap);
}

void NcursesGraphical::setMapSize(size_t height, size_t width)
{
    dynamic_cast<NcursesGame *>(_sceneList[GAME].get())->setMapSize(height, width);
}

/* COLOR */
bool NcursesGraphical::supportColor() const
{
    return _termColor;
}

void NcursesGraphical::addColor(Color color)
{
    static short id = 0;
    if (_colorIndex.find(color) != _colorIndex.end())
        return;
    if (id > COLORS - 1)
        id = 0;
    short rFinal = color.r * 4;
    short gFinal = color.g * 4;
    short bFinal = color.b * 4;
    if (rFinal > 1000) rFinal = 1000;
    if (gFinal > 1000) gFinal = 1000;
    if (bFinal > 1000) bFinal = 1000;
    init_color(id, rFinal, gFinal, bFinal);
    _colorIndex[color] = id;
    id++;
}

short NcursesGraphical::getColor(Color color)
{
    return _colorIndex[color];
}

void NcursesGraphical::initPairColor(short color1, short color2)
{
    static short id = 0;
    if (_pairColorIndex.find(std::pair<short, short>(color1, color2)) != _pairColorIndex.end())
        return;
    init_pair(id, color1, color2);
    _pairColorIndex[std::pair<short, short>(color1, color2)] = id;
    id++;
}

short NcursesGraphical::getPairColor(short color1, short color2)
{
    return _pairColorIndex[std::pair<short, short>(color1, color2)];
}

void NcursesGraphical::setUsername(const std::string &username)
{
    _username = username;
}
