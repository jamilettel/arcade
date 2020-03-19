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

namespace arc {

    class GameScene: public IScene {
    public:
        GameScene(sf::RenderWindow &window, sf::Font &font, SfmlGraphical &lib);

        void draw() override;
        void update(const sf::Event &event) override;

        void setMapSize(size_t height, size_t width);

        void setGameTitle(const std::string &title);

        void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap);

        void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls);

    private:
        SfmlGraphical &_lib;
        sf::RenderWindow &_window;
        sf::Font &_font;

        static const sf::IntRect _gameArea;
        sf::RectangleShape _gameBackground;
        sf::Text _gameTitle;

        std::vector<MySf::Button::RectButton> _buttons;
        std::optional<std::vector<std::shared_ptr<Entity>>> _gameMap;

        sf::Vector2f _cellSize;

        std::optional<const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>>> _controlsMap;

    };

}

#endif /* GAMESCENE_SCENE_HPP_ */
