/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** MainMenuScene
*/

#include "Scene/MainMenuScene.hpp"

using namespace arc;

MainMenuScene::MainMenuScene(MySDL::Window &window,
                             MySDL::Font &font,
                             SDLGraphical &lib):
    _lib(lib), _window(window), _font(font),
    _usernameInputZone(_window,
                       MySDL::Vector(1050, 50),
                       MySDL::Vector(500, 50),
                       _font,
                       "Username"),
    _title(font, "Arcade", 32, window),
    _howToPlayList(window, _howToPlayDesc, "Controls", _font, 5),
    _scoresList(window, _scoreUsers, "User", _font, 5)
{
    _exitButton = std::make_unique<MySDL::Button::RectButton>(
        _window,
        MySDL::Vector(125, 290),
        MySDL::Vector(250, 60),
        _font,
        BUTTON_COLOR,
        TEXT_COLOR,
        "Exit",
        [this] () {_window.close();});
    _title.setPosition({550, 0});
    _title.setCharacterSize(128);
    _howToPlayList.addColumn<MySDL::BasicList>(window, _howToPlayKey, "Key", _font, 5);
    _scoresList.addColumn<MySDL::BasicList>(window, _scoreValues, "Score", _font, 5);
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

void MainMenuScene::update(const SDL_Event &event)
{
    _usernameInputZone.update(event);
    _howToPlayList.update(event);
    _scoresList.update(event);
    if (_gamesList != nullptr)
        _gamesList->update(event);
    if (_graphicalList != nullptr)
        _graphicalList->update(event);
    _exitButton->update(event);
    _playButton->update(event);
}

void MainMenuScene::setFunctionPlay(const std::function<void ()> &function)
{
    _playButton = std::make_unique<MySDL::Button::RectButton>(
        _window,
        MySDL::Vector(125, 220),
        MySDL::Vector(250, 60),
        _font,
        BUTTON_COLOR,
        TEXT_COLOR,
        "Play",
        function);
    _playButton->setActivation(false);
}

void MainMenuScene::setListLibraries(const std::vector<std::string> &libraries,
                                     const std::function<void (const std::string &)> &fct,
                                     int chosen)
{
    MySDL::Vector pos(1050, 125);

    _graphicalList.release();
    _graphicalList = std::make_unique<MySDL::ButtonList>(
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
    _graphicalList->setSize(MySDL::Vector(500, 0));
}

void MainMenuScene::setListGames(const std::vector<std::string> &games,
                                 const std::function<void (const std::string &)> &fct,
                                 int chosen)
{
    MySDL::Vector pos(500, 175);

    _gamesList.release();
    _gamesList = std::make_unique<MySDL::ButtonList>(
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
    _gamesList->setSize(MySDL::Vector(500, 0));
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
    _howToPlayList.setPos(MySDL::Vector(50, 425));
    _howToPlayList.setSize(MySDL::Vector(350, 0));
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
    _scoresList.setPos(MySDL::Vector(825, 425));
    _scoresList.setSize(MySDL::Vector(500, 0));
    _scoresList.getColumn(1).setSize(MySDL::Vector(225, 0));
    _scoresList.getColumn(0).setList(_scoreUsers);
    _scoresList.getColumn(1).setList(_scoreValues);
}
