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
                       sf::Vector2f(1050, 50),
                       sf::Vector2f(500, 50),
                       _font,
                       "Username"),
    _title("Arcade", font),
    _howToPlayList(window, _howToPlayDesc, "Controls", _font, 5),
    _scoresList(window, _scoreUsers, "User", _font, 5)
{
    _exitButton = std::make_unique<MySf::Button::RectButton>(
        _window,
        sf::Vector2f(125, 290),
        sf::Vector2f(250, 60),
        _font,
        BUTTON_COLOR,
        TEXT_COLOR,
        "Exit",
        [this] () {_window.close();});
    _title.setPosition(550, 0);
    _title.setCharacterSize(128);
    _howToPlayList.addColumn<MySf::BasicList>(window, _howToPlayKey, "Key", _font, 5);
    _scoresList.addColumn<MySf::BasicList>(window, _scoreValues, "Score", _font, 5);
    _playButton = std::make_unique<MySf::Button::RectButton>(
        _window,
        sf::Vector2f(125, 220),
        sf::Vector2f(250, 60),
        _font,
        BUTTON_COLOR,
        TEXT_COLOR,
        "Play",
        [] () {});
    _playButton->setActivation(false);
}

void MainMenuScene::draw()
{
    _usernameInputZone.draw();
    if (_playButton.get())
        _playButton->draw();
    _exitButton->draw();
    if (_gamesList != nullptr)
        _gamesList->draw();
    if (_graphicalList != nullptr)
        _graphicalList->draw();
    _window.draw(_title);
    if (_howToPlayList.getList().size())
        _howToPlayList.draw();
    if (_scoresList.getList().size())
        _scoresList.draw();
}

void MainMenuScene::update(const sf::Event &event)
{
    if (_gamesList != nullptr)
        _gamesList->update(event);
    if (_graphicalList != nullptr)
        _graphicalList->update(event);
    _usernameInputZone.update(event);
    _howToPlayList.update(event);
    _scoresList.update(event);
}

void MainMenuScene::setFunctionPlay(const std::function<void ()> &function)
{
    _playButton->setFunc(function);
}

void MainMenuScene::setListLibraries(const std::vector<std::string> &libraries,
                                     const std::function<void (const std::string &)> &fct,
                                     int chosen)
{
    sf::Vector2f pos(1050, 125);

    _graphicalList.release();
    _graphicalList = std::make_unique<MySf::ButtonList>(
        _window,
        libraries,
        [fct] (const std::string &str) {
            fct(str);
        },
        "Libraries",
        _font,
        3,
        chosen);
    _graphicalList->setPos(pos);
    _graphicalList->setSize(sf::Vector2f(500, 0));
}

void MainMenuScene::setListGames(const std::vector<std::string> &games,
                                 const std::function<void (const std::string &)> &fct,
                                 int chosen)
{
    sf::Vector2f pos(500, 175);

    _gamesList.release();
    _gamesList = std::make_unique<MySf::ButtonList>(
        _window,
        games,
        [fct, this] (const std::string &str) {
            fct(str);
            _playButton->setActivation(true);
        },
        "Games",
        _font,
        2,
        chosen);
    if (chosen >= 0 && chosen < static_cast<int>(games.size()))
        _playButton->setActivation(true);
    _gamesList->setPos(pos);
    _gamesList->setSize(sf::Vector2f(500, 0));
}

void MainMenuScene::setUsername(const std::string &username)
{
    _usernameInputZone.setInput(username);
}

const std::string &MainMenuScene::getUsername()
{
    return (_usernameInputZone.getAnsiInput());
}

void MainMenuScene::setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info)
{
    _howToPlayDesc.clear();
    _howToPlayKey.clear();
    _howToPlayDesc.reserve(info.size());
    _howToPlayKey.reserve(info.size());
    std::for_each(info.begin(), info.end(),
                  [this] (const std::pair<std::string, std::string> &pair) {
                      _howToPlayDesc.emplace_back(pair.first);
                      _howToPlayKey.emplace_back(pair.second);
                  });
    _howToPlayList.setPos(sf::Vector2f(50, 425));
    _howToPlayList.setSize(sf::Vector2f(350, 0));
    _howToPlayList.getColumn(0).setList(_howToPlayDesc);
    _howToPlayList.getColumn(1).setList(_howToPlayKey);
}

void MainMenuScene::setScores(const std::vector<std::pair<std::string, std::string>> &scores)
{
    _scoreUsers.clear();
    _scoreValues.clear();
    _scoreUsers.reserve(scores.size());
    _scoreValues.reserve(scores.size());
    std::for_each(scores.begin(), scores.end(),
                  [this] (const std::pair<std::string, std::string> &pair) {
                      _scoreUsers.emplace_back(pair.first);
                      _scoreValues.emplace_back(pair.second);
                  });
    _scoresList.setPos(sf::Vector2f(825, 425));
    _scoresList.setSize(sf::Vector2f(500, 0));
    _scoresList.getColumn(1).setSize(sf::Vector2f(225, 0));
    _scoresList.getColumn(0).setList(_scoreUsers);
    _scoresList.getColumn(1).setList(_scoreValues);
}
