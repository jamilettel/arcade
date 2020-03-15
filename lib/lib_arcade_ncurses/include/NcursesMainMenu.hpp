/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_NCURSESMAINMENU_HPP
#define OOP_ARCADE_2019_NCURSESMAINMENU_HPP

#include "IScene.hpp"
#include "NcursesGraphical.hpp"
#include <panel.h>
#include <menu.h>

namespace arc
{
    class NcursesMainMenu : public IScene
    {
        public:
            NcursesMainMenu(NcursesGraphical &mainLib);
            ~NcursesMainMenu() override = default;

            void display() override;
            void refresh() override;
            void setListGames(std::vector<std::string> name, std::function<void (const std::string &)> fct, int chose);

        private:
            bool supportColor();
            void displayMainTitle();
            void createMenuGames();
            void displayMenuGames();
            void createMenuGraphics();
            void displayMenuGraphics();

        private:
            std::map<std::string, WINDOW*> _windows;
            bool _termColor;
            std::vector<std::string> _listGames;
            int _chosenGame;
            std::function<void (const std::string &)> _ftGames;

    };
}

#endif //OOP_ARCADE_2019_NCURSESMAINMENU_HPP
