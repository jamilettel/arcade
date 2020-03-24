/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "Solarfox.hpp"
#include <filesystem>
#include <fstream>
#include <cmath>

using namespace arc;

extern "C" IGame *instance_ctor() {
    return (new Solarfox);
};

Solarfox::Solarfox() try : _gameOver(false),
_moveCoordonnatePlayer(std::pair<float, float>(0, 0)),
_startTime(std::chrono::system_clock::now()),
_endTime(std::chrono::system_clock::now()),
_scoreString(std::string("0")),
_score(0),
_title("Solarfox"),
_mapWidth(60),
_mapHeight(30),
_level(0),
_started(false)
{
    srand(time(nullptr));
    this->initControlFormat();
    this->initControls();
    this->getMapFiles();
    this->loadMap(_mapFiles.at(_level));
    this->createEnemies();
    this->createPlayer();
} catch (const ArcadeError &e) {
    throw e;
}

size_t Solarfox::getMapHeight() const
{
    return _mapHeight;
}

size_t Solarfox::getMapWidth() const
{
    return _mapWidth;
}

const std::string &Solarfox::getMusic() const
{
    return _music;
}

const std::string &Solarfox::getSound() const
{
    return _sound;
}

const std::string &Solarfox::getScore()
{
    _scoreString = std::to_string(_score);
    return _scoreString;
}

const std::map<std::pair<Event::Type, Event::Key>, std::function<void()>> &Solarfox::getControls() const
{
    return _controls;
}

const std::vector<std::shared_ptr<Entity>> &Solarfox::getEntities() const
{
    return _entities;
}

const std::vector<std::pair<std::string, std::string>> &Solarfox::getGameControls() const
{
    return _gameControlsFormat;
}

const std::vector<std::pair<std::string, std::string>> &Solarfox::getGameStats() const
{
    return _gameStats;
}

void Solarfox::restart()
{
    _gameOver = false;
    _started = false;
    _entities.clear();
    _enemies.clear();
    _loots.clear();
    _moveCoordonnatesEnemies.clear();
    _moveCoordonnatePlayer = std::pair<float, float>(0, 0);
    _scoreString = std::string("0");
    _score = 0;
    _level = 0;
    this->loadMap(_mapFiles.at(0));
    this->createEnemies();
    this->createPlayer();
}

void Solarfox::updateGame()
{
    if (moveDelay()) {
        this->moveEnemies();
        this->movePlayer();
    }
    this->updateStats();
}

bool Solarfox::isGameOver() const
{
    return _gameOver;
}

const std::string &Solarfox::getTitle() const
{
    return _title;
}

void Solarfox::initControlFormat()
{
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE UP"), std::string("ARROW KEY UP")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE DOWN"), std::string("ARROW KEY DOWN")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE RIGHT"), std::string("ARROW KEY RIGHT")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE LEFT"), std::string("ARROW KEY LEFT")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("FIRE"), std::string("SPACE BAR")));
}

void Solarfox::getMapFiles()
{
    try {
        std::filesystem::directory_iterator mapDir(DIR_MAPS);

        for (auto &file: mapDir)
            if (file.path().filename().extension() == ".solarfox")
                _mapFiles.emplace_back(file.path());
    } catch (std::exception &error) {
        throw SolarfoxError(error.what());
    }
}

void Solarfox::loadMap(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    size_t x;
    size_t y;

    if (!file.good())
        throw ArcadeError("loadMap", "Unable to open file");

    while (getline(file, line)) {
        std::istringstream lineTransform(line);
        if (!(lineTransform >> x) || !(lineTransform >> y))
            continue;
        if (!invalidCoordinates(x, y))
            continue;
        std::shared_ptr<Entity> newEntity(new Entity);
        newEntity->x = x;
        newEntity->y = y;
        newEntity->spritePath = std::string("assets/solarfox/loot.png");
        newEntity->orientation = UP;
        newEntity->backgroundColor = {246, 255, 0, 1};
        newEntity->type = ENEMY;
        _loots.emplace_back(newEntity);
        _entities.emplace_back(newEntity);
    }
}

void Solarfox::updateStats()
{
    _gameStats.clear();

    _gameStats.emplace_back("Score", getScore());
    _gameStats.emplace_back("Level", std::to_string(_level));
}

bool Solarfox::invalidCoordinates(size_t x, size_t y)
{
    if (x == 0 || x >= (size_t)_mapWidth)
        return false;
    if (y == 0 || y >= (size_t)_mapHeight)
        return false;
    auto elemF = std::find_if(_entities.begin(), _entities.end(), [x, y](const std::shared_ptr<Entity> &elem){
        return elem->x == x && elem->y == y;
    });
    return !(elemF != _entities.end());
}

void Solarfox::createPlayer()
{
    _player = std::make_shared<Entity> ();
    size_t x;
    size_t y;

    do {
        x = rand() % _mapWidth;
        y = rand() % _mapHeight;
    } while (!invalidCoordinates(x, y));
    _player->x = x;
    _player->y = y;
    _player->spritePath = std::string("assets/solarfox/player.png");
    _player->orientation = UP;
    _player->backgroundColor = {42, 255, 0, 1};
    _player->type = PLAYER;
    _entities.emplace_back(_player);
}

void Solarfox::createEnemies()
{
    /* HAUT, BAS, GAUCHE, DROITE */
    std::vector<size_t> height = {0, static_cast<size_t >(_mapHeight - 1), static_cast<size_t >(rand() % _mapHeight), static_cast<size_t >(rand() % _mapHeight)};
    std::vector<size_t> width = {static_cast<size_t >(rand() % _mapWidth), static_cast<size_t >(rand() % _mapWidth), 0, static_cast<size_t >(_mapWidth - 1)};
    std::vector<Orientation> orientation = {DOWN, UP, RIGHT, LEFT};
    std::vector<std::pair<float, float>> moveCoor = {std::pair<float, float>(0.2, 0), std::pair<float, float>(-0.2, 0), std::pair<float, float>(0, 0.2), std::pair<float, float>(0, -0.2)};

    for (int i = 0; i < 4; i++) {
        std::shared_ptr<Entity> newEnemy(new Entity);
        newEnemy->x = width.at(i);
        newEnemy->y = height.at(i);
        newEnemy->spritePath = std::string("assets/solarfox/opponent.png");
        newEnemy->orientation = orientation.at(i);
        newEnemy->backgroundColor = {29, 0, 255, 1};
        newEnemy->type = ENEMY;
        _moveCoordonnatesEnemies.emplace_back(moveCoor.at(i));
        _enemies.emplace_back(newEnemy);
        _entities.emplace_back(newEnemy);
    }
}

void Solarfox::moveEnemies()
{
    /* HAUT, BAS, GAUCHE, DROITE */
    for (int i = 0; i < 2; i++) {
        if ((_enemies.at(i)->x + _moveCoordonnatesEnemies.at(i).first >
             _mapWidth && _moveCoordonnatesEnemies.at(i).first > 0) ||
            (_enemies.at(i)->x - _moveCoordonnatesEnemies.at(i).first < 0 &&
             _moveCoordonnatesEnemies.at(i).first < 0))
            _moveCoordonnatesEnemies.at(i).first = -(_moveCoordonnatesEnemies.at(i).first);
        _enemies.at(i)->x += _moveCoordonnatesEnemies.at(i).first;
    }
    for (int i = 2; i < 4; i++) {
        if ((_enemies.at(i)->y + _moveCoordonnatesEnemies.at(i).second >
             _mapHeight && _moveCoordonnatesEnemies.at(i).second > 0) ||
            (_enemies.at(i)->y - _moveCoordonnatesEnemies.at(i).second < 0 &&
             _moveCoordonnatesEnemies.at(i).second < 0))
            _moveCoordonnatesEnemies.at(i).second = -(_moveCoordonnatesEnemies.at(i).second);
        _enemies.at(i)->y += _moveCoordonnatesEnemies.at(i).second;
    }
}

bool Solarfox::moveDelay()
{
    _endTime = std::chrono::system_clock::now();
    int elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (_endTime - _startTime).count();

    if (elapsed_milliseconds > MOVE_DELAY) {
        _startTime = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

void Solarfox::initControls()
{
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::DOWN)] = [this](){
        Solarfox::moveDown();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::UP)] = [this](){
        Solarfox::moveUp();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::RIGHT)] = [this](){
        Solarfox::moveRight();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::LEFT)] = [this](){
        Solarfox::moveLeft();
    };
}

void Solarfox::moveDown()
{
    if (_moveCoordonnatePlayer.second == -0.1)
        return;
    _started = true;
    _player->x = std::round(_player->x);
    _moveCoordonnatePlayer.first = 0;
    _moveCoordonnatePlayer.second = 0.1;
}

void Solarfox::moveUp()
{
    if (_moveCoordonnatePlayer.second == 0.1)
        return;
    _started = true;
    _player->x = std::round(_player->x);
    _moveCoordonnatePlayer.first = 0;
    _moveCoordonnatePlayer.second = -0.1;
}

void Solarfox::moveRight()
{
    if (_moveCoordonnatePlayer.first == -0.1)
        return;
    _started = true;
    _player->y = std::round(_player->y);
    _moveCoordonnatePlayer.first = 0.1;
    _moveCoordonnatePlayer.second = 0;
}

void Solarfox::moveLeft()
{
    if (!_started)
        return;
    if (_moveCoordonnatePlayer.first == 0.1)
        return;
    _started = true;
    _player->y = std::round(_player->y);
    _moveCoordonnatePlayer.first = -0.1;
    _moveCoordonnatePlayer.second = 0;
}

void Solarfox::movePlayer()
{
    _player->x += _moveCoordonnatePlayer.first;
    _player->y += _moveCoordonnatePlayer.second;
}
