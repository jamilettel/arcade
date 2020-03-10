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
#define COLS_SNAKE 40
#define MOVE_DELAY 150

namespace arc {

    class Nibbler : public IGame {
    public:
        Nibbler();
        ~Nibbler() = default;

        size_t getMapHeight() const override;
        size_t getMapWidth() const override;
        const std::string &getFont() const override ;
        const std::string &getMusic() const override ;
        const std::string &getSound() const override ;
        const std::string &getScore() override ;
        const std::map<char, std::pair<std::string, Color>> &getVisualAssets() const override ;
        const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &getControls() const override;

        const std::vector<std::shared_ptr<Entity>> &getEntities() const override ;

        const std::vector<std::pair<std::string, std::string>> &getGameControlsFormatString() const override;
        const std::vector<std::string> &getGameStatsFormatString() const override;

        void restart() override;
        void updateGame() override;

        bool isGameOver() const override;

    private:
        bool _gameOver;
        std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> _controls;
        std::vector<std::pair<std::string, std::string>> _gameControlsFormat;
        std::vector<std::shared_ptr<Entity>> _entities;
        std::vector<std::string> _gameStatsFormat;
        std::string _font;
        std::string _music;
        std::string _sound;
        std::string _scoreString;
        int _score;
        std::map<char, std::pair<std::string, Color>> _visualAssets;

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

        std::shared_ptr<Entity> _snakeHead;
        std::vector<std::shared_ptr<Entity>> _snake;
        std::vector<std::shared_ptr<Entity>> _fruits;
        bool _started;
        std::pair<float, float> _moveCoordonnate;
        std::chrono::system_clock::time_point _startTime;
        std::chrono::system_clock::time_point _endTime;
    public:
    };
}

#endif //OOP_ARCADE_2019_NIBBLER_H
