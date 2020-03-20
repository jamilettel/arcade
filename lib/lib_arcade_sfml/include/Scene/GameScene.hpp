/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameScene
*/

#ifndef GAMESCENE_SCENE_HPP_
#define GAMESCENE_SCENE_HPP_

#include "Scene/IScene.hpp"
#include "MySf/Button/RectButton.hpp"
#include "Utils.hpp"
#include "SfmlGraphical.hpp"
#include "MySf/List/BasicList.hpp"

namespace arc {

    class GameScene: public IScene {
    public:
        GameScene(sf::RenderWindow &window, sf::Font &font, SfmlGraphical &lib);

        void draw() override;
        void drawPaused();
        void update(const sf::Event &event) override;

        void setMapSize(size_t height, size_t width);

        void setGameTitle(const std::string &title);

        void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap);

        void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls);

        void setGameStats(const std::vector<std::pair<std::string, std::string>> &stats);

        void setFunctionTogglePause(const std::function<void()> &function);
        void setFunctionMenu(const std::function<void()> &function);
        void setFunctionRestart(const std::function<void()> &function);

        void setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info);
        void setPause(bool status);

    private:

        SfmlGraphical &_lib;
        sf::RenderWindow &_window;
        sf::Font &_font;

        static const sf::IntRect _gameArea;
        sf::RectangleShape _gameBackground;
        sf::Text _gameTitle;

        std::optional<MySf::Button::RectButton> _pause;
        std::optional<MySf::Button::RectButton> _resume;
        std::optional<MySf::Button::RectButton> _menu;
        std::optional<MySf::Button::RectButton> _restart;
        std::optional<std::vector<std::shared_ptr<Entity>>> _gameMap;

        sf::Vector2f _cellSize;

        std::optional<const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>>> _controlsMap;

        std::vector<std::string> _gameStatList;
        MySf::BasicList _gameStats;

        bool _paused;

        sf::RectangleShape _pauseRect;
        sf::Color _pauseColorTarget;
        MySf::Color::SmoothShifting _pauseRectColor;

        std::optional<MySf::BasicList> _howToPlay;
        std::vector<std::string> _howToPlayDesc;
        std::vector<std::string> _howToPlayKeys;

    };

}

#endif /* GAMESCENE_SCENE_HPP_ */
