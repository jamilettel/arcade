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
    loadGraphicalLibrary(graphicalLib);
    refreshLibrarieLists();
}

Core::~Core()
{
    _game.release();
}

void Core::loadGameLibrary(const std::string &gamePath)
{
    DLLoader<IGame> game(gamePath);

    _game = std::unique_ptr<IGame>(game.getInstance());
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
    DLLoader<IGraphical> graphical(libPath);

    _graphical = std::unique_ptr<IGraphical>(graphical.getInstance());
    _graphical->setScene(_scene);
    _currentGraphicalLib = libPath;
    _graphical->setFont("assets/font.otf");
    setGraphicalLibFunctions();
    _graphical->setHowToPlay(getControls());
    if (std::find(_graphicalList.begin(), _graphicalList.end(), libPath) == _graphicalList.end())
        _graphicalList.push_back(libPath);
    if (_game != nullptr)
        _graphical->setControls(_game->getControls());
}

void Core::refreshLibrarieLists()
{
    _gameList.erase(_gameList.begin(), _gameList.end());
    _graphicalList.erase(_graphicalList.begin(), _graphicalList.end());

    try {
        std::filesystem::directory_iterator gameDir(GAME_DIR);
        std::filesystem::directory_iterator graphicalLibDir(GRAPHICAL_DIR);

        for (auto &file: gameDir) {
            if (file.path().filename().extension() == ".so")
                _gameList.push_back(file.path());
        }
        for (auto &file: graphicalLibDir) {
            if (file.path().filename().extension() == ".so")
                _graphicalList.push_back(file.path());
        }
    } catch (std::exception &error) {
        throw CoreError(error.what());
    }

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

    _graphical->setListGames(_gameList, [this] (const std::string &game) {_currentGame = game;}, currentGame);
    _graphical->setListLibraries(_graphicalList, [this] (const std::string &lib) {_currentGraphicalLib = lib;}, currentLib);
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
        _graphical->display();
        if (_scene == IGraphical::GAME && _game != nullptr) {
            _game->updateGame();
            _graphical->updateGameInfo(_game->getEntities());
        }
    } while (_graphical->getEventType() != Event::QUIT && !_quitGame);
}
