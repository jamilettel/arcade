/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_NIBBLER_H
#define OOP_ARCADE_2019_NIBBLER_H

#include <iostream>
#include <chrono>
#include <algorithm>
#include <memory>
#include <random>
#include "IGame.hpp"

#define ROWS_SNAKE 30
#define COLS_SNAKE 40
#define MOVE_DELAY 150

namespace arc {

    class Nibbler : public IGame {
    public:
        Nibbler();
        ~Nibbler() override = default;

        [[nodiscard]] size_t getMapHeight() const override;
        [[nodiscard]] size_t getMapWidth() const override;
        [[nodiscard]] const std::string &getMusic() const override ;
        [[nodiscard]] const std::string &getSound() const override ;
        const std::string &getScore() override ;
        [[nodiscard]] const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &getControls() const override;

        [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &getEntities() const override ;

        [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getGameControls() const override;
        [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getGameStats() const override;

        void restart() override;
        void updateGame() override;

        [[nodiscard]] bool isGameOver() const override;

        [[nodiscard]] const std::string &getTitle() const override;

    private:
        void initControlFormat();
        void initControls();
        void initSnakeHead();
        void initSnakeBody();

        void addSnakeBody();
        void generateNewFruit();
        void popFruit(std::shared_ptr<Entity> &fruit);
        void eatFruit();

        bool invalidCoordonate(float x, float y);
        std::pair<float, float> findCoordSnakeBody(float x, float y);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void moveSnake();
        bool collisionSnake();
        bool moveDelay();

        void updateStats();

    private:
        bool _gameOver;
        bool _started;

        std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> _controls;
        std::vector<std::pair<std::string, std::string>> _gameControlsFormat;

        std::string _music;
        std::string _sound;

        std::vector<std::pair<std::string, std::string>> _gameStats;
        std::string _scoreString;
        int _score;

        const std::string _title;

        std::vector<std::shared_ptr<Entity>> _entities;
        std::shared_ptr<Entity> _snakeHead;
        std::vector<std::shared_ptr<Entity>> _snake;
        std::vector<std::shared_ptr<Entity>> _fruits;

        std::pair<float, float> _moveCoordonnate;

        std::chrono::system_clock::time_point _startTime;
        std::chrono::system_clock::time_point _endTime;

        Orientation _nextMove;

        std::string _lastBodySpritePath;

    };
}

#endif //OOP_ARCADE_2019_NIBBLER_H
