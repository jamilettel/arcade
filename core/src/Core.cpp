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
#include <fstream>

using namespace arc;

Core::Core(const std::string &graphicalLib):
    _graphical(nullptr), _game(nullptr), _quitGame(false), _isPaused(false),
    _scene(IGraphical::Scene::MAIN_MENU), _changeLib(false)
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
    controls.emplace_back("Pause game", "P");
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
    if (!_graphicalLoaders.count(libPath))
        throw CoreError("Graphical libraries should be located in ./lib");
    if (libPath != _currentGraphicalLib)
        _currentGraphicalLib = libPath;

    _graphical.reset();
    std::unique_ptr<IGraphical> newLib(_graphicalLoaders[libPath]->getInstance());
    _changeLib = false;
    _graphical.swap(newLib);
    _currentGraphicalLib = libPath;
    _graphical->setScene(_scene);
    setGraphicalLibFunctions();
    _graphical->setHowToPlay(getControls());
    _graphical->setGamePause(_isPaused);
    _graphical->setUsername(_username);

    if (_game != nullptr) {
        _graphical->setControls(_game->getControls());
        _graphical->setMapSize(_game->getMapHeight(), _game->getMapWidth());
        _graphical->setGameTitle(_game->getTitle());
        _graphical->setHowToPlay(getControls());
        _graphical->setGameStats(_game->getGameStats());
    }
    sendListsToGraphicalLib();

    if (_currentGame != "") {
        getBestScoresGame();
        _graphical->setScores(_bestScoresGame);
    }
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
        getBestScoresGame();
        _graphical->setScores(_bestScoresGame);
    } catch (ArcadeError &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Core::setCurrentLib(const std::string &lib)
{
    // try {
    _changeLib = true;
    _currentGraphicalLib = lib;
        // loadGraphicalLibrary(lib);
    // } catch (ArcadeError &e) {
    //     std::cerr << e.what() << std::endl;
    // }
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
    _graphical->setFunctionTogglePause(_generalControls[std::pair(Event::KEY_PRESSED, PAUSE_GAME_KEY)]);
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
        if (_changeLib)
            loadGraphicalLibrary(_currentGraphicalLib);
        _graphical->display();
        if (_scene == IGraphical::GAME && _game != nullptr) {
            if (endGame())
                continue;
            if (!_isPaused)
                _game->updateGame();
            _graphical->updateGameInfo(_game->getEntities());
            _graphical->setGameStats(_game->getGameStats());
        }
        if (_generalControls.count(std::pair<Event::Type, Event::Key>(_graphical->getEventType(), _graphical->getKeyPressed()))) {
            _generalControls.at(std::pair<Event::Type, Event::Key>(_graphical->getEventType(), _graphical->getKeyPressed()))();
        }
        if (_graphical->getUsername() != _username)
            _username = _graphical->getUsername();
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
            _graphical->setScene(IGraphical::GAME);
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
    _generalControls[std::pair(Event::KEY_PRESSED, PAUSE_GAME_KEY)] =
        [this](){
            if (_scene != IGraphical::GAME)
                return;
            _isPaused = !_isPaused;
            _graphical->setGamePause(_isPaused);
    };
}

void Core::getBestScoresGame()
{
    std::string dirBestScores(".scores/");
    std::string path(dirBestScores + _currentGame);
    std::ifstream fileScores(path);
    std::string line;
    _bestScoresGame.clear();
    if (!fileScores.good())
        return;
    while (std::getline(fileScores, line)) {
        std::istringstream lineParse(line);
        std::pair<std::string, std::string> score;
        lineParse >> score.first;
        lineParse >> score.second;
        if (score.first != "" && score.second != "")
            _bestScoresGame.emplace_back(score);
    }
    std::sort(_bestScoresGame.begin(), _bestScoresGame.end(), [](const auto &a, const auto &b){
        return std::stoi(a.second.c_str()) >= std::stoi(b.second.c_str());
    });
    if (_bestScoresGame.size() > 10)
        _bestScoresGame.erase(_bestScoresGame.begin() + 10, _bestScoresGame.end());
    fileScores.close();
}

bool Core::endGame()
{
    if (_graphical->getScene() != IGraphical::GAME)
        return false;
    if (!_game->isGameOver())
        return false;
    _graphical->setScene(IGraphical::END_GAME);
    saveBestScore();
    _graphical->setScores(_bestScoresGame);
    _graphical->setGameStats(_game->getGameStats());
    return true;
}

void Core::saveBestScore()
{
    _bestScoresGame.emplace_back(std::pair<std::string, std::string>((_username.empty() ? "Unknown" : _username), _game->getScore()));
    std::sort(_bestScoresGame.begin(), _bestScoresGame.end(), [](const auto &a, const auto &b){
        return std::stoi(a.second.c_str()) >= std::stoi(b.second.c_str());
    });
    if (_bestScoresGame.size() > 10)
        _bestScoresGame.erase(_bestScoresGame.begin() + 10, _bestScoresGame.end());

    std::string dirBestScores(".scores/");
    std::string path(dirBestScores + _currentGame);
    std::ofstream fileScores(path);
    if (!fileScores.good())
        return;
    for (const auto &score : _bestScoresGame)
        fileScores << (score.first.empty() ? "Unknown" : score.first) << " " << score.second << std::endl;
    fileScores.close();
}
