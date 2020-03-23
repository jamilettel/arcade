/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "Solarfox.hpp"
#include <filesystem>

using namespace arc;

extern "C" IGame *instance_ctor() {
    return (new Solarfox);
};

Solarfox::Solarfox() : _gameOver(false), _scoreString(std::string("0")), _score(0), _title("Solarfox")
{
    srand(time(nullptr));
    this->initControlFormat();
    //this->getMapFiles();
}

size_t Solarfox::getMapHeight() const
{
    return ROWS_SNAKE;
}

size_t Solarfox::getMapWidth() const
{
    return COLS_SNAKE;
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
                _mapFiles.emplace_back(file.path().filename());
    } catch (std::exception &error) {
        throw SolarfoxError(error.what());
    }
}