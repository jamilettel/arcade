/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_SFML_HPP_
#define MAINMENUSCENE_SFML_HPP_

#include "Scene/IScene.hpp"
#include "MySf/Button/RectButton.hpp"
#include "Utils.hpp"
#include "SfmlGraphical.hpp"
#include "MySf/List/ButtonList.hpp"

namespace arc {

    class MainMenuScene: public IScene {
    public:
        MainMenuScene(sf::RenderWindow &window,
                      sf::Font &font,
                      SfmlGraphical &lib);

        ~MainMenuScene() = default;

        void draw() override;
        void update(const sf::Event &event) override;

        void setFunctionPlay(const std::function<void ()> &function);

        void setListGames(const std::vector<std::string> &games,
                          const std::function<void (const std::string &)> &fct,
                          int chosen = -1);
        void setListLibraries(const std::vector<std::string> &libraries,
                              const std::function<void (const std::string &)> &fct,
                              int chosen = -1);
        void setScores(const std::vector<std::pair<std::string, std::string>> &scores);

        const std::string &getUsername();
        void setUsername(const std::string &username);

        void setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info);

    private:
        SfmlGraphical &_lib;
        sf::RenderWindow &_window;
        sf::Font &_font;

        std::unique_ptr<MySf::Button::IButton> _playButton;
        std::unique_ptr<MySf::Button::IButton> _exitButton;

        MySf::InputZone _usernameInputZone;

        std::unique_ptr<MySf::ButtonList> _gamesList;
        std::unique_ptr<MySf::ButtonList> _graphicalList;
        std::vector<std::unique_ptr<MySf::Button::IButton>> _graphicalLibs;
        std::vector<std::unique_ptr<MySf::Button::IButton>> _gameLibs;

        sf::Text _title;

        std::vector<std::string> _howToPlayDesc;
        std::vector<std::string> _howToPlayKey;

        MySf::BasicList _howToPlayList;

    };

}

#endif /* MAINMENUSCENE_SFML_HPP_ */
