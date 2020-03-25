/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameOver scene
*/

#ifndef SFML_GAMEOVERSCENE_HPP_
#define SFML_GAMEOVERSCENE_HPP_

#include "Scene/IScene.hpp"
#include "SDLGraphical.hpp"
#include "List/BasicList.hpp"
#include "Button/RectButton.hpp"

namespace arc {

    class GameOverScene: public IScene {
    public:

        GameOverScene(MySDL::Window &window,
                      MySDL::Font &font,
                      SDLGraphical &lib);

        void draw();
        void update(const SDL_Event &event);

        void setFunctionMenu(const std::function<void()> &function);
        void setFunctionRestart(const std::function<void()> &function);

        void setScores(const std::vector<std::pair<std::string, std::string>> &scores);
        void setCurrentStats(const std::vector<std::string> &currentStats);

    private:

        SDLGraphical &_lib;
        MySDL::Window &_window;
        MySDL::Font &_font;

        MySDL::Text _gameOver;

        std::optional<MySDL::Button::RectButton> _restart;
        std::optional<MySDL::Button::RectButton> _menu;

        std::vector<std::string> _usernames;
        std::vector<std::string> _scores;
        MySDL::BasicList _highScores;

        MySDL::BasicList _currentStats;

    };

};

#endif /* SFML_GAMEOVERSCENE_HPP_ */
