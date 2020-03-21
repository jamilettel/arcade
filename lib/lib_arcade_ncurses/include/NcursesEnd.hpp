/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_NCURSESEND_HPP
#define OOP_ARCADE_2019_NCURSESEND_HPP

#include "IScene.hpp"
#include "NcursesGraphical.hpp"

namespace arc {

    class NcursesEnd : public IScene {
        public:
            explicit NcursesEnd(NcursesGraphical &mainLib);
            ~NcursesEnd() override;

            void display() override;
            void update() override;
            void refresh() override;

            [[nodiscard]] bool supportColor() const;

            void setGameStatsFormatString(const std::vector<std::pair<std::string, std::string>> &gameStats);

            void setScores(const std::vector<std::pair<std::string, std::string>> &scores);

        private:
            void displayTitle();
            void displayScoreUsername();
            void displayBestScores();
            void displayCommands();

        private:
            NcursesGraphical &_lib;
            std::map<std::string, WINDOW*> _windows;
            bool _termColor;
            std::optional<std::vector<std::pair<std::string, std::string>>> _gameStats;
            std::optional<std::vector<std::pair<std::string, std::string>>> _bestScores;
    };
}

#endif //OOP_ARCADE_2019_NCURSESGAME_HPP
