/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "Solarfox.hpp"
#include <filesystem>
#include <fstream>

using namespace arc;

extern "C" IGame *instance_ctor() {
    return (new Solarfox);
};

Solarfox::Solarfox() try : _gameOver(false), _scoreString(std::string("0")), _score(0), _title("Solarfox"), _mapWidth(60), _mapHeight(30), _level(0), _started(false)
{
    srand(time(nullptr));
    this->initControlFormat();
    this->getMapFiles();
    this->loadMap(_mapFiles.at(_level));
    this->createEnemies();
    this->createPlayer();
} catch (const ArcadeError &e) {
    throw e;
}

#include <iostream>
#include <memory>

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
    _scoreString = std::string("0");
    _score = 0;
    this->loadMap(_mapFiles.at(0));
    this->createEnemies();
    this->createPlayer();
}

void Solarfox::updateGame()
{

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
    std::vector<size_t> height = {0, static_cast<size_t >(_mapHeight - 1), static_cast<size_t >(rand() % _mapHeight), static_cast<size_t >(rand() % _mapHeight)};
    std::vector<size_t> width = {static_cast<size_t >(rand() % _mapWidth), static_cast<size_t >(rand() % _mapWidth), 0, static_cast<size_t >(_mapWidth - 1)};
    std::vector<Orientation> orientation = {DOWN, UP, RIGHT, LEFT};

    for (int i = 0; i < 4; i++) {
        std::shared_ptr<Entity> newEnemy(new Entity);
        newEnemy->x = width.at(i);
        newEnemy->y = height.at(i);
        newEnemy->spritePath = std::string("assets/solarfox/opponent.png");
        newEnemy->orientation = orientation.at(i);
        newEnemy->backgroundColor = {29, 0, 255, 1};
        newEnemy->type = ENEMY;
        _enemies.emplace_back(newEnemy);
        _entities.emplace_back(newEnemy);
    }
};
