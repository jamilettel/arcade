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
            void setListGames(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen);
            void setListGraphics(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen);

        public:
            void setGameTitle(std::string gameTitle);
            void setMapSize(size_t height, size_t width);

        private:
            NcursesGraphical &_lib;
            std::map<std::string, WINDOW*> _windows;
            bool _termColor;
            std::string _gameTitle;
            //std::optional<std::vector<std::string>> _listGames;
            //unsigned int _chosenGame;
            //std::optional<std::function<void (const std::string&)>> _ftGames;
            //std::optional<std::vector<std::string>> _listGraphics;
            //unsigned int _chosenGraphics;
            //std::optional<std::function<void (const std::string&)>> _ftGraphics;
            //std::optional<std::vector<std::pair<std::string, std::string>>> &_controls;

        private:
            bool supportColor() const;
            void displayTitleGame();
            void displayMap();

        private:
            std::pair<size_t, size_t> _mapSize;
    };
}

#endif //OOP_ARCADE_2019_NCURSESGAME_HPP
