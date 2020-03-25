/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameScene
*/

#include "Scene/GameScene.hpp"

using namespace arc;

const SDL_Rect GameScene::_gameArea{50, 50, 1060, 795};

GameScene::GameScene(MySDL::Window &window, MySDL::Font &font, SDLGraphical &lib):
    _lib(lib), _window(window), _font(font),
    _gameBackground(_gameArea, {0x10, 0x10, 0x10, 0xff}),
    _gameTitle(_font, "", 64, window),
    _cellHeight(0), _cellWidth(0),
    _gameStats(_window, _gameStatList, "Stats", _font, 10),
    _paused(false),
    _pauseRect({0,0}, _window.getSize()),
    _pauseColorTarget{0x20, 0x20, 0x20, 0xa0},
    _pauseRectColor(SDL_Color{0, 0, 0, 0}, 500),
    _userText(_font, "", 32, _window)
{
    _gameBackground.setPosition({_gameArea.x, _gameArea.y});
    _gameBackground.setSize({_gameArea.w, _gameArea.h});
    _gameBackground.setColor({0x10, 0x10, 0x10, 0xff});

    _pauseRectColor.setColor({_pauseColorTarget.r, _pauseColorTarget.g,
                              _pauseColorTarget.b, 0});
}

void GameScene::draw()
{
    _window.draw(_gameBackground);
    _window.draw(_gameTitle);

    if (_username != _lib.getUsername()) {
        _username = _lib.getUsername();
        _userText.setString("User: " + _username);
        _userText.setPosition({_gameArea.x, 10});
    }

    _window.draw(_userText);

    if (_gameMap.has_value()) {
        MySDL::Vector cellSize;
        cellSize.x = _cellWidth;
        cellSize.y = _cellHeight;

        for (std::shared_ptr<Entity> &entity: _gameMap.value()) {
            MySDL::Sprite &sprite = _lib.getSprite(entity->spritePath, cellSize,
                                                entity->backgroundColor);

            sprite.setPosition({static_cast<int>(_gameArea.x + _cellWidth * entity->x),
                                static_cast<int>(_gameArea.y + _cellHeight * entity->y)});

            switch (entity->orientation) {
            case (UP):
                sprite.setRotation(0);
                break;
            case (RIGHT):
                sprite.setRotation(90);
                break;
            case (DOWN):
                sprite.setRotation(180);
                break;
            case (LEFT):
                sprite.setRotation(270);
                break;
            }

            _window.draw(sprite);
        }
    }
    _gameStats.draw();
    if (_pause.has_value())
        _pause->draw();
    _pauseRect.setColor(_pauseRectColor.getColor());
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

void GameScene::update(const SDL_Event &e)
{
    std::pair<Event::Type, Event::Key> event;

    event.first = _lib.getEventType();
    event.second = _lib.getKeyPressed();
    if (_controlsMap.has_value() && _controlsMap->count(event))
        _controlsMap->at(event)();
    _gameStats.update(e);
    if (_pause.has_value())
        _pause->update(e);
    if (_paused) {
        if (_howToPlay.has_value())
            _howToPlay->update(e);
        if (_resume.has_value())
            _resume->update(e);
        if (_menu.has_value())
            _menu->update(e);
        if (_restart.has_value())
            _restart->update(e);
    }
}

void GameScene::setMapSize(size_t height, size_t width)
{
    _cellWidth = static_cast<float>(_gameArea.w) / static_cast<float>(width);
    _cellHeight = static_cast<float>(_gameArea.h) / static_cast<float>(height);
}

void GameScene::setGameTitle(const std::string &title)
{
    SDL_Rect gameTitleBounds;

    _gameTitle.setString(title);
    gameTitleBounds = _gameTitle.getRect();
    _gameTitle.setPosition({(_gameArea.x + _gameArea.w)
                            + (_window.getSize().x - _gameArea.x - _gameArea.w) / 2
                            - gameTitleBounds.w / 2, _gameArea.y});
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
        _howToPlay->addColumn<MySDL::BasicList>(_window, _howToPlayKeys, "Keys", _font, 10);
        _howToPlay->setPos({500, 175});
        _howToPlay->setSize({500, 0});
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
    _gameStats.setPos({_gameArea.x + _gameArea.w + 10, 135});
    _gameStats.setSize({_window.getSize().x - (_gameArea.x + _gameArea.w + 20), 0});
}

void GameScene::setFunctionTogglePause(const std::function<void()> &function)
{
    _pause.emplace(_window, MySDL::Vector{1230, 785}, MySDL::Vector{250, 60}, _font,
                   BUTTON_COLOR, TEXT_COLOR, "Pause", function);
    _resume.emplace(_window, MySDL::Vector{125, 220}, MySDL::Vector{250, 60}, _font,
                    BUTTON_COLOR, TEXT_COLOR, "Resume", function);
}

void GameScene::setFunctionMenu(const std::function<void()> &function)
{
    _menu.emplace(_window, MySDL::Vector{125, 360}, MySDL::Vector{250, 60}, _font,
                  BUTTON_COLOR, TEXT_COLOR, "Main Menu", function);
}

void GameScene::setPause(bool status)
{
    _paused = status;
    _pause->setUpdateState(!status);
    if (status)
        _pauseRectColor.setColor(_pauseColorTarget);
    else
        _pauseRectColor.setColor({_pauseColorTarget.r, _pauseColorTarget.g,
                                  _pauseColorTarget.b, 0});
}

void GameScene::setFunctionRestart(const std::function<void()> &function)
{
    _restart.emplace(_window, MySDL::Vector{125, 290}, MySDL::Vector{250, 60}, _font,
                     BUTTON_COLOR, TEXT_COLOR, "Restart", function);
}

const std::vector<std::string> &GameScene::getGameStats() const
{
    return (_gameStatList);
}
