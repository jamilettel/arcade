/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** MainMenuScene
*/

#include "Scene/MainMenuScene.hpp"

using namespace arc;

MainMenuScene::MainMenuScene(sf::RenderWindow &window,
                             sf::Font &font,
                             SfmlGraphical &lib):
    _lib(lib), _window(window), _font(font),
    _usernameInputZone(_window,
                       sf::Vector2f(1600 - 510, 10),
                       sf::Vector2f(500, 50),
                       _font,
                       "Username")
{
    _exitButton = std::make_unique<MySf::Button::RectButton>(
        _window,
        sf::Vector2f(100, 160),
        sf::Vector2f(200, 50),
        _font,
        BUTTON_COLOR,
        TEXT_COLOR,
        "Exit",
        [this] () {_window.close();});
}

void MainMenuScene::draw()
{
    _usernameInputZone.draw();
    if (_playButton.get())
        _playButton->draw();
    _exitButton->draw();
    for (std::unique_ptr<MySf::Button::IButton> &button: _gameLibs)
        button->draw();
}

void MainMenuScene::update(const sf::Event &event)
{
    _usernameInputZone.update(event);
}

void MainMenuScene::setFunctionPlay(const std::function<void ()> &function)
{
    _playButton = std::make_unique<MySf::Button::RectButton>(
        _window,
        sf::Vector2f(100, 100),
        sf::Vector2f(200, 50),
        _font,
        BUTTON_COLOR,
        TEXT_COLOR,
        "Play",
        function);
    _playButton->setActivation(false);
}

void MainMenuScene::setListLibraries(const std::vector<std::string> &libraries,
                                     const std::function<void (const std::string &)> &fct,
                                     int)
{
    _graphicalLibs.clear();
    _graphicalLibs.reserve(libraries.size());
}

void MainMenuScene::setListGames(const std::vector<std::string> &games,
                                 const std::function<void (const std::string &)> &fct,
                                 int)
{
    sf::Vector2f pos(500, 100);

    _gameLibs.clear();
    _gameLibs.reserve(games.size());
    for (const std::string &game: games) {
        _gameLibs.emplace_back(
            std::make_unique<MySf::Button::RectButton>(_window,
                                                       pos,
                                                       sf::Vector2f(600, 50),
                                                       _font,
                                                       BUTTON_COLOR,
                                                       TEXT_COLOR,
                                                       game,
                                                       [this, fct, game] () {
                                                           fct(game);
                                                           _playButton->setActivation(true);
                                                       }));
        pos.y += 60;
    }
}

const std::string &MainMenuScene::getUsername()
{
    return (_usernameInputZone.getAnsiInput());
}
