/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameScene
*/

#include "Scene/GameScene.hpp"

using namespace arc;

const sf::IntRect GameScene::_gameArea(50, 50, 1060, 795);

GameScene::GameScene(sf::RenderWindow &window, sf::Font &font, SfmlGraphical &lib):
    _lib(lib), _window(window), _font(font)
{
    _gameBackground.setPosition(_gameArea.left, _gameArea.top);
    _gameBackground.setSize(sf::Vector2f(_gameArea.width, _gameArea.height));
    _gameBackground.setFillColor(sf::Color(0x101010ff));
}

void GameScene::draw()
{
    _window.draw(_gameBackground);
    _window.draw(_gameTitle);

    if (_gameMap.has_value()) {
        for (std::shared_ptr<Entity> &entity: _gameMap.value()) {
            sf::Sprite &sprite = _lib.getSprite(entity->spritePath, _cellSize,
                                                entity->backgroundColor);

            sprite.setPosition(_gameArea.left + _cellSize.x * entity->x,
                               _gameArea.top + _cellSize.y * entity->y);
            _window.draw(sprite);
        }
    }
}

void GameScene::update(const sf::Event &)
{
    std::pair<Event::Type, Event::Key> event;

    event.first = _lib.getEventType();
    event.second = _lib.getKeyPressed();
    if (_controlsMap.has_value() && _controlsMap->count(event))
        _controlsMap->at(event)();
}

void GameScene::setMapSize(size_t height, size_t width)
{
    _cellSize.x = static_cast<float>(_gameArea.width) / static_cast<float>(width);
    _cellSize.y = static_cast<float>(_gameArea.height) / static_cast<float>(height);
}

void GameScene::setGameTitle(const std::string &title)
{
    sf::FloatRect gameTitleBounds;

    _gameTitle.setFont(_font);
    _gameTitle.setString(title);
    _gameTitle.setCharacterSize(64);
    gameTitleBounds = _gameTitle.getGlobalBounds();
    _gameTitle.setPosition((_gameArea.left + _gameArea.width)
                           + (_window.getSize().x - _gameArea.left - _gameArea.width) / 2
                           - gameTitleBounds.width / 2,
                           _gameArea.top);
}

void GameScene::updateGameInfo(const std::vector<std::shared_ptr<Entity> > &gameMap)
{
    _gameMap.emplace(gameMap);
}

void GameScene::setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls)
{
    _controlsMap.emplace(controls);
}
