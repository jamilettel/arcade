/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_NCURSESGAME_HPP
#define OOP_ARCADE_2019_NCURSESGAME_HPP

#include "IScene.hpp"
#include "NcursesGraphical.hpp"

namespace arc {

    class NcursesGame : public IScene {
        public:
            explicit NcursesGame(NcursesGraphical &mainLib);
            ~NcursesGame() override;

            void display() override;
            void update() override;
            void refresh() override;
            void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()> > &controls);
            void setGameTitle(std::string gameTitle);
            void setMapSize(size_t height, size_t width);
            void setGameStatsFormatString(const std::vector<std::pair<std::string, std::string>> &gameStats);

        private:
            NcursesGraphical &_lib;
            std::map<std::string, WINDOW*> _windows;
            bool _termColor;
            std::string _gameTitle;
            std::optional<std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>>> _controlsFt;

        public:
            void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap);

        private:
            bool supportColor() const;
            void displayTitleGame();
            void displayMap();
            void displayEntities();
            void displayCommands();
            void displayGameInfo();
            void displayUserName();
            void displayBestScore();

        private:
            std::pair<size_t, size_t> _mapSize;
            std::optional<std::vector<std::pair<std::string, std::string>>> &_controls;
            std::optional<std::vector<std::pair<std::string, std::string>>> _gameStats;
            std::optional<std::vector<std::shared_ptr<Entity>>> _entities;
    };
}

#endif //OOP_ARCADE_2019_NCURSESGAME_HPP
