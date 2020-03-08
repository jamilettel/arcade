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

arc::Nibbler::Nibbler()
{
    this->mapCreation();


    /*DEBUG*/
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++)
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
    for (int i = 0; i < ROWS_SNAKE; i++) {
        _map.emplace_back(std::vector<char>(COLS_SNAKE));
        for (int j = 0; j < COLS_SNAKE; j++) {
            if (i == 0 || i == ROWS_SNAKE - 1)
                _map[i][j] = '*';
            else if (j == 0 || j == COLS_SNAKE - 1)
                _map[i][j] = '*';
            else
                _map[i][j] = ' ';
        }
    }
    _map[ROWS_SNAKE / 2][COLS_SNAKE / 2] = 'G';
}

void arc::Nibbler::backgroundColorsCreation()
{
}

void arc::Nibbler::spritesCreation()
{
}