/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameScene
*/

#include "Scene/GameScene.hpp"

using namespace arc;

const sf::IntRect GameScene::_gameArea(50, 50, 1060, 795);

GameScene::GameScene(sf::RenderWindow &window,
                     sf::Font &font,
                     SfmlGraphical &lib): _lib(lib), _window(window), _font(font)
{
    _gameBackground.setPosition(_gameArea.left, _gameArea.top);
    _gameBackground.setSize(sf::Vector2f(_gameArea.width, _gameArea.height));
    _gameBackground.setFillColor(sf::Color(0x111111ff));
}

void GameScene::draw()
{
    _window.draw(_gameBackground);
}

void GameScene::update(const sf::Event &event)
{
}

void GameScene::loadSprite(const std::string &spritePath)
{
}
