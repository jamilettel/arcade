/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Core
*/

#include "Core.hpp"
#include "DLLoader.hpp"
#include <filesystem>
#include <algorithm>
#include <asm-generic/errno-base.h>

using namespace arc;

Core::Core(const std::string &graphicalLib):
    _graphical(nullptr), _game(nullptr), _quitGame(false), _isPaused(false),
    _scene(IGraphical::Scene::MAIN_MENU)
{
    initGeneralControl();
    refreshLibrarieLists();
    loadGraphicalLibrary(getDynamicLibraryName(graphicalLib));
}

Core::~Core()
{
    _game.release();
}

void Core::loadGameLibrary(const std::string &gamePath)
{
    if (!_gameLoaders.count(gamePath))
        throw CoreError("Game library couldn't be found in ./games");

    std::unique_ptr<IGame> newGame(_gameLoaders[gamePath]->getInstance());

    _game.swap(newGame);
    _oldGame.swap(newGame);
    _currentGame = gamePath;
    _graphical->setControls(_game->getControls());
    _graphical->setHowToPlay(getControls());
    _graphical->setGameStats(_game->getGameStats());
    _game->getEntities();
    _graphical->setMapSize(_game->getMapHeight(), _game->getMapWidth());
    _graphical->setGameTitle(_game->getTitle());
}

std::vector<std::pair<std::string, std::string>> Core::getControls() const
{
    std::vector<std::pair<std::string, std::string>> controls;

    controls.emplace_back("Previous library", "9");
    controls.emplace_back("Next library", "0");
    controls.emplace_back("Previous game", "7");
    controls.emplace_back("Next game", "8");
    controls.emplace_back("Restart game", "R");
    controls.emplace_back("Quit Arcade", "Escape");
    controls.emplace_back("Return to Menu", "M");
    if (_game != nullptr) {
        controls.insert(controls.end(), _game->getGameControls().begin(),
                        _game->getGameControls().end());
    }
    return (controls);
}

void Core::loadGraphicalLibrary(const std::string &libPath)
{
    if (libPath == _currentGraphicalLib)
        return;
    if (!_graphicalLoaders.count(libPath))
        throw CoreError("Graphical libraries should be located in ./lib");
    std::unique_ptr<IGraphical> newLib(_graphicalLoaders[libPath]->getInstance());
    _graphical.swap(newLib);
    _oldGraphical.swap(newLib);
    _currentGraphicalLib = libPath;
    _graphical->setScene(_scene);
    setGraphicalLibFunctions();
    _graphical->setHowToPlay(getControls());
    _graphical->setGamePause(_isPaused);

    if (_game != nullptr) {
        _graphical->setControls(_game->getControls());
        _graphical->setMapSize(_game->getMapHeight(), _game->getMapWidth());
        _graphical->setGameTitle(_game->getTitle());
        _graphical->setHowToPlay(getControls());
        _graphical->setGameStats(_game->getGameStats());
    }
    sendListsToGraphicalLib();
}

void Core::sendListsToGraphicalLib()
{
    int currentGame = -1, currentLib = -1;

    for (size_t i = 0; i < _graphicalList.size(); i++)
        if (_currentGraphicalLib == _graphicalList[i]) {
            currentLib = i;
            break;
        }
    for (size_t i = 0; i < _gameList.size(); i++)
        if (_currentGame == _gameList[i]) {
            currentGame = i;
            break;
        }

    if (_graphical != nullptr) {
        _graphical->setListGames(_gameList, [this] (const std::string &game) {setCurrentGame(game);}, currentGame);
        _graphical->setListLibraries(_graphicalList, [this] (const std::string &lib) {
                                                         setCurrentLib(lib);
                                                     }, currentLib);
    }
}

void Core::refreshLibrarieLists()
{
    _gameList.clear();
    _graphicalList.clear();
    _gameLoaders.clear();
    _graphicalLoaders.clear();

    try {
        std::filesystem::directory_iterator gameDir(GAME_DIR);
        std::filesystem::directory_iterator graphicalLibDir(GRAPHICAL_DIR);

        for (auto &file: gameDir)
            if (file.path().filename().extension() == ".so") {
                try {
                    std::string libname = getDynamicLibraryName(file.path());

                    _gameLoaders[libname] = std::make_unique<DLLoader<IGame>>(file.path());

                    _gameList.push_back(libname);
                } catch (DLLoaderError &) {}
            }

        for (auto &file: graphicalLibDir)
            if (file.path().filename().extension() == ".so") {
                try {
                    std::string libname = getDynamicLibraryName(file.path());

                    _graphicalLoaders[libname] = std::make_unique<DLLoader<IGraphical>>(file.path());
                    _graphicalList.push_back(libname);
                } catch (DLLoaderError &) {}
            }

    } catch (std::exception &error) {
        throw CoreError(error.what());
    }

    if (_graphical != nullptr)
        sendListsToGraphicalLib();
}

void Core::setCurrentGame(const std::string &game)
{
    try {
        _currentGame = game;
    } catch (ArcadeError &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Core::setCurrentLib(const std::string &lib)
{
    try {
        loadGraphicalLibrary(lib);
    } catch (ArcadeError &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Core::startGame()
{
    try {
        loadGameLibrary(_currentGame);
        _scene = IGraphical::GAME;
        _graphical->setScene(_scene);
        _graphical->setGamePause(false);
        _isPaused = false;
    } catch (ArcadeError &e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
    }
}

void Core::setGraphicalLibFunctions()
{
    _graphical->setFunctionPlay([this] () {startGame();});
    _graphical->setFunctionMenu(_generalControls[std::pair(Event::KEY_PRESSED, MENU_KEY)]);
    _graphical->setFunctionRestart(_generalControls[std::pair(Event::KEY_PRESSED, RESTART_KEY)]);
    _graphical->setFunctionTogglePause([this] () {_isPaused = !_isPaused; _graphical->setGamePause(_isPaused);});
}

const std::vector<std::string> &Core::getGameList() const
{
    return (_gameList);
}

const std::vector<std::string> &Core::getGraphicalList() const
{
    return (_graphicalList);
}

void Core::run()
{
    do {
        if (_oldGraphical != nullptr)
            _oldGraphical.reset();
        _graphical->display();
        if (_scene == IGraphical::GAME && _game != nullptr) {
            if (!_isPaused)
                _game->updateGame();
            _graphical->updateGameInfo(_game->getEntities());
            _graphical->setGameStats(_game->getGameStats());
        }
        if (_generalControls.count(std::pair<Event::Type, Event::Key>(_graphical->getEventType(), _graphical->getKeyPressed()))) {
            _generalControls.at(std::pair<Event::Type, Event::Key>(_graphical->getEventType(), _graphical->getKeyPressed()))();
        }
    } while (_graphical->getEventType() != Event::QUIT && !_quitGame);
}

std::string Core::getDynamicLibraryName(const std::string &path)
{
    std::string prefix = "/lib_arcade_";
    size_t pos = path.find(prefix);

    if (pos != std::string::npos) {
        std::string name = path.substr(pos + prefix.size(), path.size() - 3 - pos - prefix.size());

        if (name[0] >= 'a' && name[0] <= 'z')
            name[0] -= 32;
        return (name);
    }
    return (path);
}

void Core::initGeneralControl()
{
    _generalControls[std::pair(Event::KEY_PRESSED, RESTART_KEY)] = // restart
        [this](){
            if (_game != nullptr)
                _game->restart();
            _graphical->setGamePause(false);
            _isPaused = false;
        };
    _generalControls[std::pair(Event::KEY_PRESSED, QUIT_KEY)] = // quit
        [this](){
            _quitGame = true;
        };
    _generalControls[std::pair(Event::KEY_PRESSED, MENU_KEY)] = // return to menu
        [this](){
            if (_scene == IGraphical::MAIN_MENU)
                return;
            _scene = IGraphical::MAIN_MENU;
            _graphical->setScene(_scene);
            _game.release();
            _game = nullptr;
            _graphical->setHowToPlay(getControls());
        };
    _generalControls[std::pair(Event::KEY_PRESSED, PREV_LIB_KEY)] = // previous lib
        [this](){
            auto it = std::find(_graphicalList.begin(), _graphicalList.end(), _currentGraphicalLib);
            if (it == _graphicalList.begin())
                return;
            auto prevLib = std::prev(it);
            setCurrentLib(*prevLib);
        };
    _generalControls[std::pair(Event::KEY_PRESSED, NEXT_LIB_KEY)] = // next lib
        [this](){
            auto it = std::find(_graphicalList.begin(), _graphicalList.end(), _currentGraphicalLib);
            auto nextLib = std::next(it);
            if (nextLib == _graphicalList.end())
                return;
            setCurrentLib(*nextLib);
        };
    _generalControls[std::pair(Event::KEY_PRESSED, NEXT_GAME_KEY)] = // next game
        [this](){
            if (_currentGame.empty()) {
                setCurrentGame(_gameList.front());
                startGame();
            }
            auto it = std::find(_gameList.begin(), _gameList.end(), _currentGame);
            auto nextGame = std::next(it);
            if (nextGame == _gameList.end())
                return;
            setCurrentGame(*nextGame);
            startGame();
        };
    _generalControls[std::pair(Event::KEY_PRESSED, PREV_GAME_KEY)] = // prev game
        [this](){
            if (_currentGame.empty()) {
                setCurrentGame(_gameList.front());
                startGame();
            }
            auto it = std::find(_gameList.begin(), _gameList.end(), _currentGame);
            if (it == _gameList.begin())
                return;
            auto prevGame = std::prev(it);
            setCurrentGame(*prevGame);
            startGame();
        };
}
