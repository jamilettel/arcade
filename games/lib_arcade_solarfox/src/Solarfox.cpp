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

Solarfox::Solarfox() try : _gameOver(false), _scoreString(std::string("0")), _score(0), _title("Solarfox"), _mapWidth(0), _mapHeight(0), _level(0)
{
    srand(time(nullptr));
    this->initControlFormat();
    this->getMapFiles();
    this->loadMap(_mapFiles.at(_level));
} catch (const ArcadeError &e) {
    throw e;
}

#include <iostream>

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

}

void Solarfox::updateGame()
{

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
    std::istringstream lineTransform;

    if (!file.good())
        throw ArcadeError("loadMap", "Unable to open file");

    getline(file, line);
    lineTransform.str(line);
    lineTransform >> _mapHeight;

    getline(file, line);
    lineTransform.clear();
    lineTransform.str(line);
    lineTransform >> _mapWidth;

}
