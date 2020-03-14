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

namespace arc
{
    class NcursesMainMenu : public IScene
    {
        public:
            NcursesMainMenu();
            ~NcursesMainMenu() override;

            void display() override;
            void refresh() override;

        private:
            void createMainTitle();
            void displayMainTitle();
            void createMenuGames();
            void displayMenuGames();
            void createMenuGraphics();
            void displayMenuGraphics();

        private:
            std::map<std::string, WINDOW*> _windows;
            std::map<std::string, PANEL*> _panel;

    };
}

#endif //OOP_ARCADE_2019_NCURSESMAINMENU_HPP
