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

arc::Nibbler::Nibbler() : _gameOver(false), _controls(initControls())
{
    srand(time(nullptr));
    this->initSnakeHead();
    this->generateNewFruit();
}

void arc::Nibbler::initControlFormat()
{
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE UP"), std::string("ARROW KEY UP")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE DOWN"), std::string("ARROW KEY DOWN")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE RIGHT"), std::string("ARROW KEY RIGHT")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE LEFT"), std::string("ARROW KEY LEFT")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("RESTART"), std::string("R")));
}

std::map<std::pair<arc::Event::Type, arc::Event::Key>, std::function<void ()>> arc::Nibbler::initControls()
{
    std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> controls;
    controls[std::pair<Event::Type, Event::Key>(Event::KEY_RELEASED, Event::DOWN)] = [this](){
        arc::Nibbler::moveDown();
    };
    controls[std::pair<Event::Type, Event::Key>(Event::KEY_RELEASED, Event::UP)] = [this](){
        arc::Nibbler::moveUp();
    };
    controls[std::pair<Event::Type, Event::Key>(Event::KEY_RELEASED, Event::RIGHT)] = [this](){
        arc::Nibbler::moveRight();
    };
    controls[std::pair<Event::Type, Event::Key>(Event::KEY_RELEASED, Event::LEFT)] = [this](){
        arc::Nibbler::moveLeft();
    };
    return controls;
}

void arc::Nibbler::moveDown()
{

}

void arc::Nibbler::moveUp()
{

}

void arc::Nibbler::moveRight()
{

}

void arc::Nibbler::moveLeft()
{

}

void arc::Nibbler::updateGame()
{
}

void arc::Nibbler::restart()
{
    _gameOver = false;
    _entities.clear();
    _snake.clear();
    _fruits.clear();
    this->initSnakeHead();
    this->generateNewFruit();
}

void arc::Nibbler::initSnakeHead()
{
    _snakeHead->spritePath = "";
    _snakeHead->orientation = UP;
    _snakeHead->backgroundColor = {244, 255, 40, 1};
    _snakeHead->x = rand() % COLS_SNAKE + 1;
    _snakeHead->y = rand() % ROWS_SNAKE + 1;
    do {
        _snakeHead->x = rand() % COLS_SNAKE + 1;
        _snakeHead->y = rand() % ROWS_SNAKE + 1;
    } while (invalidCoordonate(_snakeHead->x, _snakeHead->y));
    _entities.emplace_back(*_snakeHead);
}

void arc::Nibbler::generateNewFruit()
{
    Entity *newFruit = new Entity;
    newFruit->spritePath = "";
    newFruit->orientation = UP;
    newFruit->backgroundColor = {255, 51, 40, 1};
    do {
        newFruit->x = rand() % COLS_SNAKE + 1;
        newFruit->y = rand() % ROWS_SNAKE + 1;
    } while (invalidCoordonate(newFruit->x, newFruit->y));

    _entities.emplace_back(*newFruit);
    _fruits.emplace_back(newFruit);
}

void arc::Nibbler::popFruit(Entity fruit)
{
    _entities.erase(std::remove(_entities.begin(), _entities.end(), fruit), _entities.end());
    _fruits.erase(std::remove(_fruits.begin(), _fruits.end(),&fruit), _fruits.end());
}

void arc::Nibbler::eatFruit(Entity fruit)
{
    do {
        fruit.x = rand() % COLS_SNAKE + 1;
        fruit.y = rand() % ROWS_SNAKE + 1;
    } while (invalidCoordonate(fruit.x, fruit.y));
}

bool arc::Nibbler::invalidCoordonate(float x, float y)
{
    auto elemF = find_if(_entities.begin(), _entities.end(), [x, y](const Entity &elem)
    {
        return elem.x == x && elem.y == y;
    });
    return elemF != _entities.end();
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

int arc::Nibbler::moveDelay()
{
    _endTime = std::chrono::system_clock::now();

    int elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (_endTime - _startTime).count();

    std::cout << elapsed_milliseconds << std::endl;
    return 1;
}
 */