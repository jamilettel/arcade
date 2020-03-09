/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_NIBBLER_H
#define OOP_ARCADE_2019_NIBBLER_H

#include "IGame.hpp"
#include <iostream>
#include <chrono>

#define ROWS_SNAKE 20
#define COLS_SNAKE 20

namespace arc {

    class Nibbler : public IGame {
    public:
        Nibbler();
        ~Nibbler() = default;

        size_t getMapHeight() const override;
        size_t getMapWidth() const override;

        const std::vector<std::pair<std::string, std::string>> &getGameControlsFormatString() const override;

        void restart() override;
        void updateGame() override;

        const std::vector<Entity> &getEntities() const override ;
        const std::vector<std::string> &getGameStatsFormatString() const override;

        bool isGameOver() const override;

        const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &getControls() const override;

    private:
        bool _gameOver;
        std::vector<std::pair<std::string, std::string>> _gameControlsFormat;
        std::vector<Entity> _entities;
        std::vector<std::string> _gameStatsFormat;
        const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> _controls;

    private:
        void initControlFormat();
        std::map<std::pair<arc::Event::Type, arc::Event::Key>, std::function<void ()>> initControls();
        void initSnakeHead();
        void generateNewFruit();
        void popFruit(Entity fruit);
        void eatFruit(Entity fruit);
        bool invalidCoordonate(float x, float y);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        Entity *_snakeHead;
        std::vector<Entity*> _snake;
        std::vector<Entity*> _fruits;
        //std::pair<float, float> _moveCoordonnate;
    public:
    };
}
#endif //OOP_ARCADE_2019_NIBBLER_H
