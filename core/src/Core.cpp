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
    _graphical(nullptr), _game(nullptr), _quitGame(false), _isPaused(false)
{
    refreshLibrarieLists();
    loadGraphicalLibrary(graphicalLib);
}

void Core::loadGameLibrary(const std::string &gamePath)
{
    DLLoader<IGame> game(gamePath);

    _game = std::unique_ptr<IGame>(game.getInstance());
    _currentGraphicalLib = gamePath;
    _graphical->setControls(_game->getControls());
    _graphical->setHowToPlay(getControls());
    if (std::find(_graphicalList.begin(), _graphicalList.end(), gamePath) == _graphicalList.end())
        _graphicalList.push_back(gamePath);
}

std::vector<std::pair<std::string, std::string>> Core::getControls() const
{
    std::vector<std::pair<std::string, std::string>> controls;

    controls.push_back(std::pair<std::string, std::string>("Previous library", "9"));
    controls.push_back(std::pair<std::string, std::string>("Next library", "0"));
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
    _graphical->setScene(IGraphical::MAIN_MENU);
    _currentGraphicalLib = libPath;
    setGraphicalLibFunctions();
}

void Core::refreshLibrarieLists()
{
    _gameList.erase(_gameList.begin(), _gameList.end());
    _graphicalList.erase(_graphicalList.begin(), _graphicalList.end());

    try {
        std::filesystem::directory_iterator gameDir(GAME_DIR);
        std::filesystem::directory_iterator graphicalLibDir(GRAPHICAL_DIR);

        for (auto &file: gameDir) {
            _gameList.push_back(file.path());
        }
        for (auto &file: graphicalLibDir) {
            _graphicalList.push_back(file.path());
        }
    } catch (std::exception &error) {
        throw CoreError(error.what());
    }
}

void Core::startGame()
{
    loadGameLibrary(_currentGame);
    _graphical->setScene(IGraphical::GAME);
}

void Core::setGraphicalLibFunctions()
{
    _graphical->setFunctionPlay([this] () {startGame();});
    _graphical->setFunctionMenu([this] () {
                                    _graphical->setScene(IGraphical::MAIN_MENU);
                                    _game.release();
                                    _game = nullptr;
                                });
    _graphical->setFunctionRestart([this] () {
                                       _game->restart();
                                       _graphical->setScene(IGraphical::GAME);
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
    while (_graphical->getEventType() != Event::QUIT && !_quitGame) {
        _graphical->display();
        // if (_graphical->getSceneChoice(_graphical->getScene()));
    }
}
