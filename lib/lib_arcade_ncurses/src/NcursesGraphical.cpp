/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SfmlGraphical
*/

#include "NcursesError.hpp"
#include "NcursesGraphical.hpp"
#include "NcursesMainMenu.hpp"

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
    if (supportColor()) {
        start_color();
        initColor();
    }
    _sceneList[MAIN_MENU] = std::shared_ptr<IScene>(new NcursesMainMenu(*this));
}

NcursesGraphical::~NcursesGraphical()
{
    echo();
    nocbreak();
    endwin();
}

void NcursesGraphical::display()
{
    checkEvents();
    erase();
    if (LINES < 24 || COLS < 150) {
        mvprintw((LINES / 2), (COLS / 2) - (21 / 2),
                 "window size too small");
    } else {
        _sceneList[MAIN_MENU]->display();
        _sceneList[MAIN_MENU]->refresh();
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
    //static_cast<NcursesGameScene *>(_sceneList.at(GAME).get())->setControls(controls);
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
    _gameTitle = game;
}

void NcursesGraphical::setListGames(const std::vector<std::string> &games, const std::function<void(const std::string &)> &fct, int chosen)
{
    static_cast<NcursesMainMenu *>(_sceneList[getScene()].get())->setListGames(games, fct, chosen);
}

void NcursesGraphical::setListLibraries(const std::vector<std::string> &libraries, const std::function<void(const std::string &)> &fct, int chosen)
{
    static_cast<NcursesMainMenu *>(_sceneList[getScene()].get())->setListGraphics(libraries, fct, chosen);
}

void NcursesGraphical::setFunctionPlay(const std::function<void()> &function)
{

}

void NcursesGraphical::setFunctionMenu(const std::function<void()> &function)
{

}

void NcursesGraphical::setFunctionTogglePause(const std::function<void()> &function)
{

}

void NcursesGraphical::setFunctionRestart(const std::function<void()> &function)
{

}

void NcursesGraphical::setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info)
{

}

void NcursesGraphical::setGameStatsFormatString(const std::vector<std::string> &info)
{

}

void NcursesGraphical::setFont(const std::string &font)
{

}

void NcursesGraphical::setVisualAssets(const std::map<char, std::pair<std::string, Color> > &sprites)
{

}

void NcursesGraphical::updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap)
{

}

void NcursesGraphical::setMusic(const std::string &music)
{

}

void NcursesGraphical::playSound(const std::string &sound)
{

}

void NcursesGraphical::setMapSize(size_t height, size_t width)
{

}

/* COLOR */
bool NcursesGraphical::supportColor() const
{
    return _termColor;
}

void NcursesGraphical::initColor() const
{
    init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(BLACK_BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(GREEN_BLUE, COLOR_GREEN, COLOR_BLUE);
    init_pair(RED_BLUE, COLOR_RED, COLOR_BLUE);
    init_pair(RED_WHITE, COLOR_RED, COLOR_WHITE);
    init_pair(YELLOW_BLUE, COLOR_YELLOW, COLOR_BLUE);
}
