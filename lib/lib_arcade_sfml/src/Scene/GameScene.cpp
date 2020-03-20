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
    _lib(lib), _window(window), _font(font),
    _gameStats(_window, _gameStatList, "Stats", _font, 10),
    _paused(false), _pauseColorTarget(sf::Color(0x202020a0)), _pauseRectColor(sf::Color(0), 500)
{
    _gameBackground.setPosition(_gameArea.left, _gameArea.top);
    _gameBackground.setSize(sf::Vector2f(_gameArea.width, _gameArea.height));
    _gameBackground.setFillColor(sf::Color(0x101010ff));

    sf::Vector2u screenSize = _window.getSize();
    _pauseRect.setSize(sf::Vector2f(screenSize.x, screenSize.y));
    _pauseRectColor.setColor(sf::Color(_pauseColorTarget.r, _pauseColorTarget.g,
                                       _pauseColorTarget.b, 0));
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
    _gameStats.draw();
    if (_pause.has_value())
        _pause->draw();
    _pauseRect.setFillColor(_pauseRectColor.getColor());
    _window.draw(_pauseRect);
    if (_paused)
        drawPaused();
}

void GameScene::drawPaused()
{
    if (_resume.has_value())
        _resume->draw();
    if (_menu.has_value())
        _menu->draw();
    if (_restart.has_value())
        _restart->draw();
    if (_howToPlay.has_value())
        _howToPlay->draw();
}

void GameScene::update(const sf::Event &e)
{
    std::pair<Event::Type, Event::Key> event;

    event.first = _lib.getEventType();
    event.second = _lib.getKeyPressed();
    if (_controlsMap.has_value() && _controlsMap->count(event))
        _controlsMap->at(event)();
    _gameStats.update(e);
    if (_paused) {
        if (_howToPlay.has_value())
            _howToPlay->update(e);
    }
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
void GameScene::setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info)
{
    _howToPlayDesc.clear();
    _howToPlayKeys.clear();
    _howToPlayDesc.reserve(info.size());
    _howToPlayKeys.reserve(info.size());
    std::for_each(info.begin(), info.end(),
                  [this] (const std::pair<std::string, std::string> &pair) {
                      _howToPlayDesc.emplace_back(pair.first);
                      _howToPlayKeys.emplace_back(pair.second);
                  });
    if (!_howToPlay.has_value()) {
        _howToPlay.emplace(_window, _howToPlayDesc, "Controls", _font, 10);
        _howToPlay->addColumn<MySf::BasicList>(_window, _howToPlayKeys, "Keys", _font, 10);
        _howToPlay->setPos(sf::Vector2f(500, 175));
        _howToPlay->setSize(sf::Vector2f(500, 0));
    }
    _howToPlay->setList(_howToPlayDesc);
    _howToPlay->getColumn(1).setList(_howToPlayKeys);
}

void GameScene::setGameStats(const std::vector<std::pair<std::string, std::string> > &stats)
{
    _gameStatList.clear();
    _gameStatList.reserve(stats.size());
    std::for_each(stats.begin(),
                  stats.end(), [this] (const std::pair<std::string, std::string> &pair) {
                                   _gameStatList.emplace_back(pair.first + ": " + pair.second);
                               });
    _gameStats.setList(_gameStatList);
    _gameStats.setPos(sf::Vector2f(_gameArea.left + _gameArea.width + 10, 135));
    _gameStats.setSize(sf::Vector2f(_window.getSize().x - (_gameArea.left + _gameArea.width + 20), 0));
}

void GameScene::setFunctionTogglePause(const std::function<void()> &function)
{
    _pause.emplace(_window, sf::Vector2f(1230, 785), sf::Vector2f(250, 60), _font,
                   BUTTON_COLOR, TEXT_COLOR, "Pause", function);
    _resume.emplace(_window, sf::Vector2f(125, 220), sf::Vector2f(250, 60), _font,
                    BUTTON_COLOR, TEXT_COLOR, "Resume", function);
}

void GameScene::setFunctionMenu(const std::function<void()> &function)
{
    _menu.emplace(_window, sf::Vector2f(125, 360), sf::Vector2f(250, 60), _font,
                  BUTTON_COLOR, TEXT_COLOR, "Main Menu", function);
}

void GameScene::setPause(bool status)
{
    _paused = status;
    _pause->setUpdateState(!status);
    if (status)
        _pauseRectColor.setColor(_pauseColorTarget);
    else
        _pauseRectColor.setColor(sf::Color(_pauseColorTarget.r, _pauseColorTarget.g,
                                           _pauseColorTarget.b, 0));
}

void GameScene::setFunctionRestart(const std::function<void()> &function)
{
    _restart.emplace(_window, sf::Vector2f(125, 290), sf::Vector2f(250, 60), _font,
                     BUTTON_COLOR, TEXT_COLOR, "Restart", function);
}
