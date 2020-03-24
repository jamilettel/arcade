/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_SOLARFOX_HPP
#define OOP_ARCADE_2019_SOLARFOX_HPP

#include <chrono>
#include "IGame.hpp"
#include "SolarfoxError.hpp"

#define DIR_MAPS "games/lib_arcade_solarfox/maps/"
#define MOVE_DELAY 15

namespace arc
{
    class Solarfox : public IGame {
        public:
            Solarfox();
            ~Solarfox() override = default;

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

            void moveEnemies();

        private:
            bool _gameOver;
            std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> _controls;
            std::vector<std::pair<std::string, std::string>> _gameControlsFormat;

            std::vector<std::shared_ptr<Entity>> _entities;
            std::vector<std::shared_ptr<Entity>> _loots;
            std::vector<std::shared_ptr<Entity>> _enemies;
            std::vector<std::pair<float, float>> _moveCoordonnatesEnemies;
            std::shared_ptr<Entity> _player;
            std::pair<float, float> _moveCoordonnatePlayer;

            std::chrono::system_clock::time_point _startTime;
            std::chrono::system_clock::time_point _endTime;

            std::vector<std::pair<std::string, std::string>> _gameStats;

            std::string _music;
            std::string _sound;

            std::string _scoreString;
            int _score;

            const std::string _title;

            std::vector<std::string> _mapFiles;

            int _mapWidth;
            int _mapHeight;

            unsigned int _level;

            bool _started;

        private:
            void initControlFormat();
            void initControls();

            void getMapFiles();
            void loadMap(const std::string &filepath);
            bool invalidCoordinates(size_t x, size_t y);

            void createPlayer();
            void createEnemies();

            void updateStats();

            bool moveDelay();

            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();
            void movePlayer();

        private:
    };
}

#endif //OOP_ARCADE_2019_SOLARFOX_HPP
