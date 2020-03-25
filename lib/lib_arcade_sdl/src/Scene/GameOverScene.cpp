/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Game Over scene
*/

#include "Scene/GameOverScene.hpp"

using namespace arc;

GameOverScene::GameOverScene(MySDL::Window &window,
                             MySDL::Font &font,
                             SDLGraphical &lib):
    _lib(lib), _window(window), _font(font), _gameOver(_font, "GAME OVER", 128, _window),
    _highScores(_window, _usernames, "Username", _font),
    _currentStats(_window, std::vector<std::string>(), "Current Stats", _font, 9)
{
    _highScores.addColumn<MySDL::BasicList>(_window, _scores, "Scores", _font);
    _highScores.setPos({50, 185});
    _highScores.setSize({530, 0});
    _gameOver.setPosition({400, 20});

    _currentStats.setPos({1120, 135});
    _currentStats.setSize({470, 0});
}

void GameOverScene::update(const SDL_Event &event)
{
    _highScores.update(event);
    _currentStats.update(event);
    if (_restart.has_value())
        _restart->update(event);
    if (_menu.has_value())
        _menu->update(event);
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
    _menu.emplace(_window, MySDL::Vector{1230, 785}, MySDL::Vector{260, 60}, _font,
                  BUTTON_COLOR, TEXT_COLOR, "Main Menu", function);
}

void GameOverScene::setFunctionRestart(const std::function<void ()> &function)
{
    if (_restart.has_value()) {
        _restart->setFunc(function);
        return;
    }
    _restart.emplace(_window, MySDL::Vector{1230, 715}, MySDL::Vector{260, 60}, _font,
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
