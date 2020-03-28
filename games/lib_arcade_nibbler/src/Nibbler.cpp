/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "Nibbler.hpp"

extern "C" arc::IGame *instance_ctor() {
    return (new arc::Nibbler);
};

arc::Nibbler::Nibbler() :
_gameOver(false),
_started(false),
_scoreString(std::string("0")),
_score(0), _title("Nibbler"),
_moveCoordonnate(std::pair<float, float>(0, 0)),
_startTime(std::chrono::system_clock::now()),
_nextMove(RIGHT)
{
    this->initControls();
    this->initControlFormat();
    this->initSnakeHead();
    this->initSnakeBody();
    this->generateNewFruit();
}

void arc::Nibbler::initControlFormat()
{
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE UP"), std::string("ARROW KEY UP")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE DOWN"), std::string("ARROW KEY DOWN")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE RIGHT"), std::string("ARROW KEY RIGHT")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE LEFT"), std::string("ARROW KEY LEFT")));
}

void arc::Nibbler::initControls()
{
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::DOWN)] = [this](){
        arc::Nibbler::moveDown();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::UP)] = [this](){
        arc::Nibbler::moveUp();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::RIGHT)] = [this](){
        arc::Nibbler::moveRight();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::LEFT)] = [this](){
        arc::Nibbler::moveLeft();
    };
}

void arc::Nibbler::moveDown()
{
    if (_moveCoordonnate.second == -1)
        return;
    _started = true;
    _nextMove = DOWN;
}

void arc::Nibbler::moveUp()
{
    if (_moveCoordonnate.second == 1)
        return;
    _started = true;
    _nextMove = UP;
}

void arc::Nibbler::moveRight()
{
    if (_moveCoordonnate.first == -1)
        return;
    _started = true;
    _nextMove = RIGHT;
}

void arc::Nibbler::moveLeft()
{
    if (!_started)
        return;
    if (_moveCoordonnate.first == 1)
        return;
    _nextMove = LEFT;
}

void arc::Nibbler::moveSnake()
{
    float x = _snakeHead->x;
    float y = _snakeHead->y;
    Orientation rotate;

    switch (_nextMove) {
    case (UP):
        _moveCoordonnate.first = 0;
        _moveCoordonnate.second = -1;
        _snakeHead->orientation = UP;
        break;
    case (RIGHT):
        _moveCoordonnate.first = 1;
        _moveCoordonnate.second = 0;
        _snakeHead->orientation = RIGHT;
        break;
    case (DOWN):
        _moveCoordonnate.first = 0;
        _moveCoordonnate.second = 1;
        _snakeHead->orientation = DOWN;
        break;
    case (LEFT):
        _moveCoordonnate.first = -1;
        _moveCoordonnate.second = 0;
        _snakeHead->orientation = LEFT;
        break;
    }

    _snakeHead->x += _moveCoordonnate.first;
    _snakeHead->y += _moveCoordonnate.second;
    rotate = _snakeHead->orientation;
    for_each(_snake.begin(), _snake.end(),
             [&x, &y, &rotate](std::shared_ptr<Entity> &body) {
                 float old_x = body->x;
                 float old_y = body->y;
                 Orientation old_rotate = body->orientation;
                 body->x = x;
                 body->y = y;
                 body->orientation = rotate;
                 if (body->orientation == LEFT && old_rotate == UP)
                     body->spritePath = "assets/nibbler/SnakeCorner2.png";
                 else if (body->orientation == UP && old_rotate == LEFT)
                     body->spritePath = "assets/nibbler/SnakeCorner.png";
                 else if (body->orientation < old_rotate)
                     body->spritePath = "assets/nibbler/SnakeCorner2.png";
                 else if (body->orientation > old_rotate)
                     body->spritePath = "assets/nibbler/SnakeCorner.png";
                 else
                     body->spritePath = "assets/nibbler/SnakeBody.png";
                 x = old_x;
                 y = old_y;
                 rotate = old_rotate;
             });
    if (_snake.size() > 1) {
        _lastBodySpritePath = _snake[_snake.size() - 2]->spritePath;
        _snake[_snake.size() - 2]->spritePath = "assets/nibbler/SnakeTail.png";
    }
}

bool arc::Nibbler::collisionSnake()
{
    if (_snakeHead->x >= COLS_SNAKE || _snakeHead->y >= ROWS_SNAKE || _snakeHead->x < 0 || _snakeHead->y < 0)
        return true;
    auto elemF = find_if(_snake.begin(), _snake.end(), [this](const std::shared_ptr<Entity> &elem)
    {
        return elem->x == _snakeHead->x && elem->y == _snakeHead->y;
    });
    return elemF != _snake.end();
}

void arc::Nibbler::updateGame()
{
    if (!_started) return;
    if (!this->moveDelay())
        return;
    this->moveSnake();
    if (this->collisionSnake()) {
        _gameOver = true;
    }
    this->eatFruit();
    this->updateStats();
}

void arc::Nibbler::restart()
{
    _gameOver = false;
    _started = false;
    _entities.clear();
    _snake.clear();
    _fruits.clear();
    _scoreString = std::string("0");
    _score = 0;
    this->initSnakeHead();
    this->initSnakeBody();
    this->generateNewFruit();
}

void arc::Nibbler::initSnakeHead()
{
    _snakeHead = std::make_shared<Entity>();
    _snakeHead->spritePath = std::string("assets/nibbler/SnakeHead.png");
    _snakeHead->orientation = RIGHT;
    _snakeHead->backgroundColor = {242, 255, 0, 255};
    _snakeHead->x = (COLS_SNAKE + 1) / 2;
    _snakeHead->y = (ROWS_SNAKE + 1) / 2;
    _entities.emplace_back(_snakeHead);
}

void arc::Nibbler::initSnakeBody()
{
    this->addSnakeBody();
    this->addSnakeBody();
    this->addSnakeBody();
    this->addSnakeBody();
}

void arc::Nibbler::addSnakeBody()
{
    std::shared_ptr<Entity> newBody(new Entity);
    std::pair<float, float> validCoordBody;
    newBody->spritePath = "assets/nibbler/SnakeTail.png";
    newBody->orientation = RIGHT;
    newBody->backgroundColor = {69, 245, 66, 255};

    if (_snake.empty())
        validCoordBody = findCoordSnakeBody(_snakeHead->x, _snakeHead->y);
    else {
        validCoordBody = findCoordSnakeBody(_snake.back()->x, _snake.back()->y);
        if (_snake.size() > 1) {
            if (_lastBodySpritePath != "")
                _snake[_snake.size() - 2]->spritePath = _lastBodySpritePath;
            else
            _snake[_snake.size() - 2]->spritePath = "assets/nibbler/SnakeBody.png";
            _snake.back()->spritePath = "assets/nibbler/SnakeTail.png";
        }
    }

    if (validCoordBody.first == -2 && validCoordBody.second == -2) {
        _gameOver = true;
        return;
    }
    newBody->x = validCoordBody.first;
    newBody->y = validCoordBody.second;

    if (_snake.size())
        _entities.emplace_back(_snake.back());
    _snake.emplace_back(newBody);
}

std::pair<float, float> arc::Nibbler::findCoordSnakeBody(float x, float y)
{
    const auto findObjLeft = std::find_if(_entities.begin(), _entities.end(), [x, y](std::shared_ptr<Entity> const &obj){
        return obj->x == (x - 1) && obj->y == y;
    });
    if (findObjLeft == _entities.end())
        return std::pair<float, float>(x - 1, y);

    const auto findObjBottom = std::find_if(_entities.begin(), _entities.end(), [x, y](std::shared_ptr<Entity> const &obj){
        return obj->x == x && obj->y == (y + 1);
    });
    if (findObjBottom == _entities.end())
        return std::pair<float, float>(x, (y + 1));

    const auto &findObjRight = std::find_if(_entities.begin(), _entities.end(), [x, y](std::shared_ptr<Entity> const &obj){
        return obj->x == (x + 1) && obj->y == y;
    });
    if (findObjRight == _entities.end())
        return std::pair<float, float>(x + 1, y);

    const auto &findObjTop = std::find_if(_entities.begin(), _entities.end(), [x, y](std::shared_ptr<Entity> const &obj){
        return obj->x == x && obj->y == (y - 1);
    });
    if (findObjTop == _entities.end())
        return std::pair<float, float>(x, (y - 1));

    return std::pair<float, float>(-2, -2);
}

void arc::Nibbler::generateNewFruit()
{
    std::shared_ptr<Entity> newFruit(new Entity);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> ranX {0, COLS_SNAKE - 1};
    std::uniform_int_distribution<int> ranY {0, ROWS_SNAKE - 1};
    newFruit->spritePath = std::string("assets/nibbler/Fruit.png");
    newFruit->orientation = UP;
    newFruit->backgroundColor = {255, 51, 40, 255};

    do {
        newFruit->x = ranX(re);
        newFruit->y = ranY(re);
    } while (!invalidCoordonate(newFruit->x, newFruit->y));
    _entities.emplace_back(newFruit);
    _fruits.emplace_back(newFruit);
}

void arc::Nibbler::popFruit(std::shared_ptr<Entity> &fruit)
{
    _entities.erase(std::remove(_entities.begin(), _entities.end(), fruit), _entities.end());
    _fruits.erase(std::remove(_fruits.begin(), _fruits.end(), fruit), _fruits.end());
}

void arc::Nibbler::eatFruit()
{
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> ranX {0, COLS_SNAKE - 1};
    std::uniform_int_distribution<int> ranY {0, ROWS_SNAKE - 1};
    float newX = 0;
    float newY = 0;
    for (auto &fruit : _fruits) {
        if (fruit->x == _snakeHead->x && fruit->y == _snakeHead->y) {
            _score++;
            this->addSnakeBody();
            if (_gameOver)
                return;
            do {
                newX = ranX(re);
                newY = ranY(re);
            } while (!invalidCoordonate(newX, newY));
            fruit->x = newX;
            fruit->y = newY;
        }
    }
}

bool arc::Nibbler::invalidCoordonate(float x, float y)
{
    auto elemF = find_if(_entities.begin(), _entities.end(), [x, y](const std::shared_ptr<Entity> &elem)
    {
        return elem->x == x && elem->y == y;
    });
    return elemF == _entities.end();
}

bool arc::Nibbler::moveDelay()
{
    _endTime = std::chrono::system_clock::now();
    int elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (_endTime - _startTime).count();

    if (elapsed_milliseconds > MOVE_DELAY) {
        _startTime = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

size_t arc::Nibbler::getMapWidth() const
{
    return COLS_SNAKE;
}

size_t arc::Nibbler::getMapHeight() const
{
    return ROWS_SNAKE;
}

const std::map<std::pair<arc::Event::Type, arc::Event::Key>, std::function<void ()> > & arc::Nibbler::getControls() const
{
    return _controls;
}

const std::vector<std::shared_ptr<arc::Entity>> & arc::Nibbler::getEntities() const
{
    return _entities;
}

bool arc::Nibbler::isGameOver() const
{
    return _gameOver;
}

const std::string &arc::Nibbler::getScore()
{
    _scoreString = std::to_string(_score);
    return _scoreString;
}

const std::string &arc::Nibbler::getMusic() const
{
    return _music;
}

const std::string &arc::Nibbler::getSound() const
{
    return _sound;
}

void arc::Nibbler::updateStats()
{
    _gameStats.clear();

    _gameStats.emplace_back("Score", getScore());
    _gameStats.emplace_back("Size of the snake", std::to_string(_snake.size() + 1));
    _gameStats.emplace_back("Fruits on the map", std::to_string(_fruits.size()));
}

const std::vector<std::pair<std::string, std::string>> &arc::Nibbler::getGameStats() const
{
    return _gameStats;
}

const std::vector<std::pair<std::string, std::string> > & arc::Nibbler::getGameControls() const
{
    return _gameControlsFormat;
}

const std::string &arc::Nibbler::getTitle() const
{
    return _title;
}
