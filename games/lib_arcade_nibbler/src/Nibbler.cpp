/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include <algorithm>
#include "Nibbler.hpp"

extern "C" arc::IGame *instance_ctor() {
    return (new arc::Nibbler);
};

arc::Nibbler::Nibbler() : _gameOver(false)
{
}

void arc::Nibbler::updateGame()
{
}

void arc::Nibbler::restart()
{
    _gameOver = false;
    _entities.clear();
}

void arc::Nibbler::initSnakeHead()
{
    _snakeHead->spritePath = "";
    _snakeHead->orientation = UP;
    _snakeHead->backgroundColor = {244, 255, 40, 1};
    _snakeHead->x = rand() % COLS_SNAKE + 1;
    _snakeHead->y = rand() % ROWS_SNAKE + 1;
    _entities.emplace_back(*_snakeHead);
}

void arc::Nibbler::generateNewFruit()
{
    Entity *newFruit = new Entity;
    newFruit->spritePath = "";
    newFruit->orientation = UP;
    newFruit->backgroundColor = {255, 51, 40, 1};
    newFruit->x = rand() % COLS_SNAKE + 1;
    newFruit->y = rand() % ROWS_SNAKE + 1;

    _entities.emplace_back(*newFruit);
    _fruits.emplace_back(newFruit);
}

void arc::Nibbler::popFruit(Entity fruit)
{
    _entities.erase(std::remove(_entities.begin(), _entities.end(), fruit), _entities.end());
    _fruits.erase(std::remove(_fruits.begin(), _fruits.end(),&fruit), _fruits.end());
}

size_t arc::Nibbler::getMapWidth() const
{
    return COLS_SNAKE;
}

size_t arc::Nibbler::getMapHeight() const
{
    return ROWS_SNAKE;
}

const std::vector<std::pair<std::string, std::string> > & arc::Nibbler::getGameControlsFormatString() const
{
    return _gameControlsFormat;
}

const std::map<std::pair<arc::Event::Type, arc::Event::Key>, std::function<void ()> > & arc::Nibbler::getControls() const
{
    return _controls;
}

const std::vector<arc::Entity> & arc::Nibbler::getEntities() const
{
    return _entities;
}

const std::vector<std::string> & arc::Nibbler::getGameStatsFormatString() const
{
    return _gameStatsFormat;
}

bool arc::Nibbler::isGameOver() const
{
    return _gameOver;
}

/*

 arc::Nibbler::Nibbler() : _fruit(-1, -1), _snakeHead(-1, -1), _startTime(std::chrono::system_clock::now())
{
    srand(time(NULL));
    this->mapCreation();
    this->initSnakeHead();
    this->generateFruit();
for (size_t i = 0; i < _map.size(); i++) {
for (size_t j = 0; j < _map[i].size(); j++)
std::cout << _map[i][j] << " ";
std::cout << std::endl;
}
}

void arc::Nibbler::moveSnake()
{
    std::cout << "test" << std::endl;
}

int arc::Nibbler::moveDelay()
{
    _endTime = std::chrono::system_clock::now();

    int elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (_endTime - _startTime).count();

    std::cout << elapsed_milliseconds << std::endl;
    return 1;
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
    if (_snakeHead.first != -1 && _snakeHead.second != -1)
        return;
    do {
        _snakeHead.first = rand() % (ROWS_SNAKE - 1) + 1;
        _snakeHead.second = rand() % (COLS_SNAKE - 1) + 1;
    } while (_map[_snakeHead.first][_snakeHead.second] != ' ');
    _map[_snakeHead.first][_snakeHead.second] = 'S';
}

void arc::Nibbler::generateFruit()
{
    if (_fruit.first != -1 && _fruit.second != -1)
        return;
    do {
        _fruit.first = rand() % (ROWS_SNAKE - 1) + 1;
        _fruit.second = rand() % (COLS_SNAKE - 1) + 1;
    } while (_map[_fruit.first][_fruit.second] != ' ');
    _map[_fruit.first][_fruit.second] = 'F';
}

 */