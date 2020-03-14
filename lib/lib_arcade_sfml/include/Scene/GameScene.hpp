/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameScene
*/

#ifndef GAMESCENE_SCENE_HPP_
#define GAMESCENE_SCENE_HPP_

#include "Scene/IScene.hpp"
#include "Button/RectButton.hpp"
#include "Utils.hpp"
#include "SfmlGraphical.hpp"

namespace arc {

    class GameScene: public IScene {
    public:
        GameScene(sf::RenderWindow &window,
                  sf::Font &font,
                  SfmlGraphical &lib);

        void draw() override;
        void update(const sf::Event &event) override;

    private:
        void loadSprite(const std::string &spritePath);

        SfmlGraphical &_lib;
        sf::RenderWindow &_window;
        sf::Font &_font;

        static const sf::IntRect _gameArea;
        sf::RectangleShape _gameBackground;

        std::vector<MySf::Button::RectButton> _buttons;
        std::optional<std::vector<std::shared_ptr<Entity>>> _gameMap;

        sf::Vector2f _cellSize;

        size_t _mapHeight;
        size_t _mapWidth;

    };

}

#endif /* GAMESCENE_SCENE_HPP_ */
