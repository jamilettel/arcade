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

using namespace arc;

Core::Core(const std::string &graphicalLib):
    _graphical(nullptr), _game(nullptr), _quitGame(false), _isPaused(false),
    _scene(IGraphical::Scene::MAIN_MENU)
{
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
    _game->getEntities();
    _graphical->setMapSize(_game->getMapHeight(), _game->getMapWidth());
    _graphical->setGameTitle(_game->getTitle());
}

std::vector<std::pair<std::string, std::string>> Core::getControls() const
{
    std::vector<std::pair<std::string, std::string>> controls;

    controls.push_back(std::pair<std::string, std::string>("Previous library", "9"));
    controls.push_back(std::pair<std::string, std::string>("Next library", "0"));
    controls.push_back(std::pair<std::string, std::string>("Previous game", "7"));
    controls.push_back(std::pair<std::string, std::string>("Next game", "8"));
    if (_game != nullptr) {
        controls.insert(controls.end(), _game->getGameControlsFormatString().begin(),
                        _game->getGameControlsFormatString().end());
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
    _graphical->setFont("assets/font.otf");
    _graphical->setScene(_scene);
    setGraphicalLibFunctions();
    _graphical->setHowToPlay(getControls());

    if (_game != nullptr)
        _graphical->setControls(_game->getControls());
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
    _currentGame = game;
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
    } catch (ArcadeError &e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
    }
}

void Core::setGraphicalLibFunctions()
{
    _graphical->setFunctionPlay([this] () {startGame();});
    _graphical->setFunctionMenu([this] () {
                                    _scene = IGraphical::MAIN_MENU;
                                    _graphical->setScene(_scene);
                                    _game.release();
                                    _game = nullptr;
                                });
    _graphical->setFunctionRestart([this] () {
                                       _game->restart();
                                       _scene = IGraphical::GAME;
                                       _graphical->setScene(_scene);
                                   });
    _graphical->setFunctionTogglePause([this] () {_isPaused = !_isPaused;});
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
            _game->updateGame();
            _graphical->updateGameInfo(_game->getEntities());
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
