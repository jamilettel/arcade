/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include <iostream>
#include "Nibbler.hpp"

extern "C" arc::IGame *instance_ctor() {
    return (new arc::Nibbler);
};

arc::Nibbler::Nibbler() : _fruit(-1, -1), _snakeHead(-1, -1)
{
    srand (time(NULL));
    this->mapCreation();
    this->initSnakeHead();
    this->generateFruit();


    /*DEBUG*/
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++)
            std::cout << _map[i][j] << " ";
        std::cout << std::endl;
    }
}

arc::Nibbler::~Nibbler()
{

}

const std::vector<std::vector<char> > & arc::Nibbler::getMap() const
{
    return _map;
}

const std::map<char, arc::Color> & arc::Nibbler::getBackgroundColors() const
{
    return _backgroundColors;
}

const std::map<char, std::string> & arc::Nibbler::getSprites() const
{
    return _sprites;
}

const std::string & arc::Nibbler::getGameControlsFormatString() const
{
    return _gameControlsFormatString;
}

void arc::Nibbler::restart()
{
    this->mapCreation();
    this->initSnakeHead();
    this->generateFruit();
}

void arc::Nibbler::updateGame(Event::Type type, Event::Key keyPressed)
{
}

const std::string & arc::Nibbler::getGameStatsFormatString() const
{
    return _gameStatsFormatString;
}

void arc::Nibbler::mapCreation()
{
    _map.clear();
    for (size_t i = 0; i < ROWS_SNAKE; i++) {
        _map.emplace_back(std::vector<char>(COLS_SNAKE));
        for (size_t j = 0; j < COLS_SNAKE; j++) {
            if (i == 0 || i == ROWS_SNAKE - 1)
                _map[i][j] = '*';
            else if (j == 0 || j == COLS_SNAKE - 1)
                _map[i][j] = '*';
            else
                _map[i][j] = ' ';
        }
    }
}

void arc::Nibbler::initSnakeHead()
{
    do {
        if (_snakeHead.first == -1 && _snakeHead.second == -1) {
            _snakeHead.first = rand() % (ROWS_SNAKE - 1) + 1;
            _snakeHead.second = rand() % (COLS_SNAKE - 1) + 1;
        }
    } while (_map[_snakeHead.first][_snakeHead.second] != ' ');
    _map[_snakeHead.first][_snakeHead.second] = 'S';
}

void arc::Nibbler::generateFruit()
{
    do {
        if (_fruit.first == -1 && _fruit.second == -1) {
            _fruit.first = rand() % (ROWS_SNAKE - 1) + 1;
            _fruit.second = rand() % (COLS_SNAKE - 1) + 1;
        }
    } while (_map[_fruit.first][_fruit.second] != ' ');
    _map[_fruit.first][_fruit.second] = 'F';
}

void arc::Nibbler::backgroundColorsCreation()
{
}

void arc::Nibbler::spritesCreation()
{
}