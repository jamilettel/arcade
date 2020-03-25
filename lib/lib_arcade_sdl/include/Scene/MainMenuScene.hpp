/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_SFML_HPP_
#define MAINMENUSCENE_SFML_HPP_

#include "Scene/IScene.hpp"
#include "Button/RectButton.hpp"
#include "Utils.hpp"
#include "SDLGraphical.hpp"
#include "List/ButtonList.hpp"

namespace arc {

    class MainMenuScene: public IScene {
    public:
        MainMenuScene(MySDL::Window &window,
                      MySDL::Font &font,
                      SDLGraphical &lib);

        ~MainMenuScene() = default;

        void draw() override;
        void update(const SDL_Event &event) override;

        void setFunctionPlay(const std::function<void ()> &function);

        void setListGames(const std::vector<std::string> &games,
                          const std::function<void (const std::string &)> &fct,
                          int chosen = -1);
        void setListLibraries(const std::vector<std::string> &libraries,
                              const std::function<void (const std::string &)> &fct,
                              int chosen = -1);
        const std::string &getUsername();
        void setUsername(const std::string &username);

        void setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info);
        void setScores(const std::vector<std::pair<std::string, std::string>> &scores);

    private:
        SDLGraphical &_lib;
        MySDL::Window &_window;
        MySDL::Font &_font;

        std::unique_ptr<MySDL::Button::IButton> _playButton;
        std::unique_ptr<MySDL::Button::IButton> _exitButton;

        MySDL::InputZone _usernameInputZone;

        std::unique_ptr<MySDL::ButtonList> _gamesList;
        std::unique_ptr<MySDL::ButtonList> _graphicalList;
        std::vector<std::unique_ptr<MySDL::Button::IButton>> _graphicalLibs;
        std::vector<std::unique_ptr<MySDL::Button::IButton>> _gameLibs;

        MySDL::Text _title;

        std::vector<std::string> _howToPlayDesc;
        std::vector<std::string> _howToPlayKey;

        MySDL::BasicList _howToPlayList;

        std::vector<std::string> _scoreUsers;
        std::vector<std::string> _scoreValues;

        MySDL::BasicList _scoresList;

    };

}

#endif /* MAINMENUSCENE_SFML_HPP_ */
