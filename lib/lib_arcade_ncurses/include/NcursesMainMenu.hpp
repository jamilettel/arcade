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
            void update() override;
            void refresh() override;
            void setListGames(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen);
            void setListGraphics(const std::vector<std::string> &name, const std::function<void (const std::string &)> &fct, int chosen);

        private:
            bool supportColor();
            void displayMainTitle();
            void displayMenuGames();
            void displayMenuGraphics();
            void displayInfo();


        private:
            NcursesGraphical &_lib;
            std::map<std::string, WINDOW*> _windows;
            bool _termColor;
            int _activeMenu;
            std::optional<std::vector<std::string>> _listGames;
            unsigned int _chosenGame;
            std::optional<std::function<void (const std::string&)>> _ftGames;
            std::optional<std::vector<std::string>> _listGraphics;
            unsigned int _chosenGraphics;
            std::optional<std::function<void (const std::string&)>> _ftGraphics;
            std::optional<std::vector<std::pair<std::string, std::string>>> &_controls;

    };
}

#endif //OOP_ARCADE_2019_NCURSESMAINMENU_HPP
