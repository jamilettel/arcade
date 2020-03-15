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
    {97, Event::A},
    {98, Event::B},
    {99, Event::C},
    {100, Event::D},
    {101, Event::E},
    {102, Event::F},
    {103, Event::G},
    {104, Event::H},
    {105, Event::I},
    {106, Event::J},
    {107, Event::K},
    {108, Event::L},
    {109, Event::M},
    {110, Event::N},
    {111, Event::O},
    {112, Event::P},
    {113, Event::Q},
    {114, Event::R},
    {115, Event::S},
    {116, Event::T},
    {117, Event::U},
    {118, Event::V},
    {119, Event::W},
    {120, Event::X},
    {121, Event::Y},
    {122, Event::Z},
    {KEY_BACKSPACE, Event::BACKSPACE},
    {9, Event::TAB},
    {27, Event::ESCAPE},
    {330, Event::DELETE},
    {KEY_UP, Event::UP},
    {KEY_DOWN, Event::DOWN},
    {KEY_LEFT, Event::LEFT},
    {KEY_RIGHT, Event::RIGHT},
    {331, Event::INSERT},
    {258, Event::PAGEUP},
    {259, Event::PAGEDOWN},
    {48, Event::NUM0},
    {49, Event::NUM1},
    {50, Event::NUM2},
    {51, Event::NUM3},
    {52, Event::NUM4},
    {53, Event::NUM5},
    {54, Event::NUM6},
    {55, Event::NUM7},
    {56, Event::NUM8},
    {57, Event::NUM9},
    {KEY_F(1), Event::F1},
    {KEY_F(2), Event::F2},
    {KEY_F(3), Event::F3},
    {KEY_F(4), Event::F4},
    {KEY_F(5), Event::F5},
    {KEY_F(6), Event::F6},
    {KEY_F(7), Event::F7},
    {KEY_F(8), Event::F8},
    {KEY_F(9), Event::F9},
    {KEY_F(10), Event::F10},
    {KEY_F(11), Event::F11},
    {KEY_F(12), Event::F12},
};

NcursesGraphical::NcursesGraphical() : _eventType(Event::NO_EVENT), _keyPressed(Event::NONE), _scene(MAIN_MENU)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
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
        _eventType = Event::KEY_PRESSED;
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
