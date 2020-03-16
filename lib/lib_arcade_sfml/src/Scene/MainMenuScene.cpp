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
    // for (std::unique_ptr<MySf::Button::IButton> &button: _gameLibs)
    //     button->draw();
    if (_gamesList != nullptr)
        _gamesList->draw();
    if (_graphicalList != nullptr)
        _graphicalList->draw();
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
                                     const std::function<void (const std::string &)> &,
                                     int chosen)
{
    sf::Vector2f pos(1050, 100);

    _graphicalList.release();
    _graphicalList = std::make_unique<MySf::List>(
        _window,
        libraries,
        [] (const std::string &) {
            // fct(str);
            // _playButton->setActivation(true);
        },
        "Libraries",
        _font,
        chosen);
    _graphicalList->setPos(pos);
    _graphicalList->setSize(sf::Vector2f(500, 0));
}

void MainMenuScene::setListGames(const std::vector<std::string> &games,
                                 const std::function<void (const std::string &)> &fct,
                                 int chosen)
{
    sf::Vector2f pos(500, 100);

    _gamesList.release();
    _gamesList = std::make_unique<MySf::List>(
        _window,
        games,
        [fct, this] (const std::string &str) {
            fct(str);
            _playButton->setActivation(true);
        },
        "Games",
        _font,
        chosen);
    _gamesList->setPos(pos);
    _gamesList->setSize(sf::Vector2f(500, 0));
}

const std::string &MainMenuScene::getUsername()
{
    return (_usernameInputZone.getAnsiInput());
}
