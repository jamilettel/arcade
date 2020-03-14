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

namespace arc
{
    class NcursesMainMenu : public IScene
    {
        public:
            NcursesMainMenu();
            ~NcursesMainMenu() override;

            void display() override;

        private:
            void displayMainMenu();
            void displayMainTitle();

        private:
            std::map<std::string, WINDOW*> _mainMenuBox;

    };
}

#endif //OOP_ARCADE_2019_NCURSESMAINMENU_HPP
