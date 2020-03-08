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

Core::Core(const std::string &graphicalLib): _quitGame(false)
{
    refreshLibrarieLists();
    loadGraphicalLibrary(graphicalLib);
    loadGameLibrary("games/lib_arcade_nibbler.so");
    setMenuOptions();
    setPauseOptions();
    refreshLibrarieLists();
}

void Core::loadGameLibrary(const std::string &gamePath)
{
    // std::string gamePath = GAME_DIR + name;
    DLLoader<IGame> game(gamePath);

    _game = std::unique_ptr<IGame>(game.getInstance());
    _currentGraphicalLib = gamePath;
}

void Core::loadGraphicalLibrary(const std::string &libPath)
{
    // std::string libPath = GRAPHICAL_DIR + name;
    DLLoader<IGraphical> graphical(libPath);

    _graphical = std::unique_ptr<IGraphical>(graphical.getInstance());
    _graphical->setMainMenuOptions(_mainMenuOptions);
    _graphical->setPauseMenuOptions(_pauseMenuOptions);
    _graphical->setScene(IGraphical::MAIN_MENU);
    _currentGraphicalLib = libPath;
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

void Core::setMenuOptions()
{
    // _mainMenuOptions.push_back("Choose game");
    // _mainMenuOptions.push_back("Change library");
    // _mainMenuOptions.push_back("How to play");
    // _mainMenuOptions.push_back("Quit");
    _mainMenuOptions["Quit"] =
        [this] () {
            _quitGame = true;
        };
}

void Core::setPauseOptions()
{
    _mainMenuOptions["Resume"] =
        [this] () {
            _graphical->setScene(IGraphical::GAME);
        };
    // _mainMenuOptions.push_back("Resume");
    // _mainMenuOptions.push_back("Change library");
    // _mainMenuOptions.push_back("How to play");
    // _mainMenuOptions.push_back("Return to menu");
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
