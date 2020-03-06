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

Core::Core(const std::string &graphicalLib)
{
    refreshLibrarieLists();
    loadGraphicalLibrary(graphicalLib);
    setMenuOptions();
    setPauseOptions();
    refreshLibrarieLists();
}

void Core::loadGameLibrary(const std::string &name)
{
    std::string gamePath = GAME_DIR + name;
    DLLoader<IGame> game(gamePath);

    _game = std::unique_ptr<IGame>(game.getInstance());
    _currentGraphicalLib = name;
}

void Core::loadGraphicalLibrary(const std::string &name)
{
    std::string libPath = GRAPHICAL_DIR + name;
    DLLoader<IGraphical> graphical(libPath);

    _graphical = std::unique_ptr<IGraphical>(graphical.getInstance());
    _graphical->setMainMenuOptions(_mainMenuOptions);
    _graphical->setPauseMenuOptions(_pauseMenuOptions);
    _graphical->setScene(IGraphical::MAIN_MENU);
    _currentGraphicalLib = name;
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
}

void Core::setPauseOptions()
{
    std::map<std::string, std::function<void()>> a;

    _mainMenuOptions["Resume"] =
        [this] () {
            _graphical->setScene(IGraphical::GAME);
        };
    // _mainMenuOptions["Change Library"] =
    //     [this] () {
    //     };
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
    while (_graphical->getEventType() != Event::QUIT) {
        _graphical->display();
        // if (_graphical->getSceneChoice(_graphical->getScene()));
    }
}
