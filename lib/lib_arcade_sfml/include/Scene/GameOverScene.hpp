/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameOver scene
*/

#ifndef SFML_GAMEOVERSCENE_HPP_
#define SFML_GAMEOVERSCENE_HPP_

#include "Scene/IScene.hpp"
#include "SfmlGraphical.hpp"
#include "MySf/List/BasicList.hpp"
#include "MySf/Button/RectButton.hpp"

namespace arc {

    class GameOverScene: public IScene {
    public:

        GameOverScene(sf::RenderWindow &window,
                      sf::Font &font,
                      SfmlGraphical &lib);

        void draw();
        void update(const sf::Event &event);

        void setFunctionMenu(const std::function<void()> &function);
        void setFunctionRestart(const std::function<void()> &function);

        void setScores(const std::vector<std::pair<std::string, std::string>> &scores);
        void setCurrentStats(const std::vector<std::string> &currentStats);

    private:

        SfmlGraphical &_lib;
        sf::RenderWindow &_window;
        sf::Font &_font;

        sf::Text _gameOver;

        std::optional<MySf::Button::RectButton> _restart;
        std::optional<MySf::Button::RectButton> _menu;

        std::vector<std::string> _usernames;
        std::vector<std::string> _scores;
        MySf::BasicList _highScores;

        MySf::BasicList _currentStats;

    };

};

#endif /* SFML_GAMEOVERSCENE_HPP_ */
