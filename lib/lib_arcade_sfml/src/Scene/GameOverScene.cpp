/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Game Over scene
*/

#include "Scene/GameOverScene.hpp"

using namespace arc;

GameOverScene::GameOverScene(sf::RenderWindow &window,
                             sf::Font &font,
                             SfmlGraphical &lib):
    _lib(lib), _window(window), _font(font), _gameOver("GAME OVER", _font),
    _highScores(_window, _usernames, "Username", _font),
    _currentStats(_window, std::vector<std::string>(), "Current Stats", _font, 9)
{
    _highScores.addColumn<MySf::BasicList>(_window, _scores, "Scores", _font);
    _highScores.setPos(sf::Vector2f(50, 185));
    _highScores.setSize(sf::Vector2f(530, 0));
    _gameOver.setCharacterSize(128);
    _gameOver.setPosition(400, 20);

    _currentStats.setPos(sf::Vector2f(1120, 135));
    _currentStats.setSize(sf::Vector2f(470, 0));
}

void GameOverScene::update(const sf::Event &event)
{
    _highScores.update(event);
}

void GameOverScene::draw()
{
    _highScores.draw();
    _currentStats.draw();
    if (_restart.has_value())
        _restart->draw();
    if (_menu.has_value())
        _menu->draw();
    _window.draw(_gameOver);
}

void GameOverScene::setFunctionMenu(const std::function<void ()> &function)
{
    if (_menu.has_value()) {
        _menu->setFunc(function);
        return;
    }
    _menu.emplace(_window, sf::Vector2f(1230, 785), sf::Vector2f(260, 60), _font,
                  BUTTON_COLOR, TEXT_COLOR, "Main Menu", function);
}

void GameOverScene::setFunctionRestart(const std::function<void ()> &function)
{
    if (_restart.has_value()) {
        _restart->setFunc(function);
        return;
    }
    _restart.emplace(_window, sf::Vector2f(1230, 715), sf::Vector2f(260, 60), _font,
                     BUTTON_COLOR, TEXT_COLOR, "Restart", function);
}

void GameOverScene::setScores(const std::vector<std::pair<std::string, std::string> > &scores)
{
    _scores.clear();
    _usernames.clear();
    _scores.reserve(scores.size());
    _usernames.reserve(scores.size());

    std::for_each(scores.begin(), scores.end(),
                  [this] (const std::pair<std::string, std::string> &score) {
                      _usernames.emplace_back(score.first);
                      _scores.emplace_back(score.second);
                  });

    _highScores.setList(_usernames);
    _highScores.getColumn(1).setList(_scores);
}

void GameOverScene::setCurrentStats(const std::vector<std::string> &currentStats)
{
    _currentStats.setList(currentStats);
}
