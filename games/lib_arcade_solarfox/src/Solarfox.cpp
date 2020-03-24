/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#include "Solarfox.hpp"
#include <filesystem>
#include <fstream>
#include <cmath>

using namespace arc;

extern "C" IGame *instance_ctor() {
    return (new Solarfox);
};

Solarfox::Solarfox() try : _gameOver(false),
_startTime(std::chrono::system_clock::now()),
_endTime(std::chrono::system_clock::now()),
_scoreString(std::string("0")),
_score(0),
_title("Solarfox"),
_mapWidth(60),
_mapHeight(30),
_level(0),
_powerups(0),
_started(false)
{
    srand(time(nullptr));
    this->initControlFormat();
    this->initControls();
    this->getMapFiles();
    this->loadMap(_mapFiles.at(_level));
    this->createEnemies();
    this->createPlayer();
} catch (const ArcadeError &e) {
    throw e;
}

size_t Solarfox::getMapHeight() const
{
    return _mapHeight;
}

size_t Solarfox::getMapWidth() const
{
    return _mapWidth;
}

const std::string &Solarfox::getMusic() const
{
    return _music;
}

const std::string &Solarfox::getSound() const
{
    return _sound;
}

const std::string &Solarfox::getScore()
{
    _scoreString = std::to_string(_score);
    return _scoreString;
}

const std::map<std::pair<Event::Type, Event::Key>, std::function<void()>> &Solarfox::getControls() const
{
    return _controls;
}

const std::vector<std::shared_ptr<Entity>> &Solarfox::getEntities() const
{
    return _entities;
}

const std::vector<std::pair<std::string, std::string>> &Solarfox::getGameControls() const
{
    return _gameControlsFormat;
}

const std::vector<std::pair<std::string, std::string>> &Solarfox::getGameStats() const
{
    return _gameStats;
}

void Solarfox::restart()
{
    _gameOver = false;
    _started = false;
    _entities.clear();
    _enemies.clear();
    _loots.clear();
    _shootsPlayer.clear();
    _shootsEnemies.clear();
    _scoreString = std::string("0");
    _score = 0;
    _level = 0;
    this->loadMap(_mapFiles.at(0));
    this->createEnemies();
    this->createPlayer();
}

void Solarfox::updateGame()
{
    if (!moveDelay())
        return;
    this->moveEnemies();
    this->createShootEnemy();
    this->movePlayer();
    this->moveShootsPlayer();
    this->moveShootsEnemy();
    //this->detectAttackEnemies();
    //this->detectCounterAttack();
    //this->detectFirePowerups();
    //this->detectPlayerDeath();
    this->updateStats();
}

bool Solarfox::isGameOver() const
{
    return _gameOver;
}

const std::string &Solarfox::getTitle() const
{
    return _title;
}

void Solarfox::initControlFormat()
{
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE UP"), std::string("ARROW KEY UP")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE DOWN"), std::string("ARROW KEY DOWN")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE RIGHT"), std::string("ARROW KEY RIGHT")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("MOVE LEFT"), std::string("ARROW KEY LEFT")));
    _gameControlsFormat.emplace_back(std::pair <std::string, std::string>(std::string("FIRE"), std::string("S")));
}

void Solarfox::getMapFiles()
{
    try {
        std::filesystem::directory_iterator mapDir(DIR_MAPS);

        for (auto &file: mapDir)
            if (file.path().filename().extension() == ".solarfox")
                _mapFiles.emplace_back(file.path());
    } catch (std::exception &error) {
        throw SolarfoxError(error.what());
    }
}

void Solarfox::loadMap(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    size_t x;
    size_t y;

    if (!file.good())
        throw ArcadeError("loadMap", "Unable to open file");

    while (getline(file, line)) {
        std::istringstream lineTransform(line);
        if (!(lineTransform >> x) || !(lineTransform >> y))
            continue;
        if (!invalidCoordinates(x, y))
            continue;
        std::shared_ptr<Entity> newEntity(new Entity);
        newEntity->x = x;
        newEntity->y = y;
        newEntity->spritePath = std::string("assets/solarfox/Loot.png");
        newEntity->orientation = UP;
        newEntity->backgroundColor = {246, 255, 0, 1};
        newEntity->type = ENEMY;
        _loots.emplace_back(newEntity);
        _entities.emplace_back(newEntity);
    }
}

void Solarfox::updateStats()
{
    _gameStats.clear();

    _gameStats.emplace_back("Score", getScore());
    _gameStats.emplace_back("Level", std::to_string(_level));
    _gameStats.emplace_back("PowerUps", std::to_string(_powerups));
}

bool Solarfox::invalidCoordinates(size_t x, size_t y)
{
    if (x == 0 || x >= (size_t)_mapWidth)
        return false;
    if (y == 0 || y >= (size_t)_mapHeight)
        return false;
    auto elemF = std::find_if(_entities.begin(), _entities.end(), [x, y](const std::shared_ptr<Entity> &elem){
        return elem->x == x && elem->y == y;
    });
    return !(elemF != _entities.end());
}

void Solarfox::createPlayer()
{
    _player.first = std::make_shared<Entity> ();
    _player.second = std::pair<float, float>(0, 0);
    size_t x;
    size_t y;

    do {
        x = rand() % _mapWidth;
        y = rand() % _mapHeight;
    } while (!invalidCoordinates(x, y));
    _player.first->x = x;
    _player.first->y = y;
    _player.first->spritePath = std::string("assets/solarfox/Player.png");
    _player.first->orientation = UP;
    _player.first->backgroundColor = {42, 255, 0, 1};
    _player.first->type = PLAYER;
    _entities.emplace_back(_player.first);
}

void Solarfox::createEnemies()
{
    /* HAUT, BAS, GAUCHE, DROITE */
    std::vector<size_t> height = {0, static_cast<size_t >(_mapHeight - 1), static_cast<size_t >(rand() % _mapHeight), static_cast<size_t >(rand() % _mapHeight)};
    std::vector<size_t> width = {static_cast<size_t >(rand() % _mapWidth), static_cast<size_t >(rand() % _mapWidth), 0, static_cast<size_t >(_mapWidth - 1)};
    std::vector<Orientation> orientation = {DOWN, UP, RIGHT, LEFT};
    std::vector<std::pair<float, float>> moveCoor = {std::pair<float, float>(MOVE_VALUE, 0), std::pair<float, float>(-MOVE_VALUE, 0), std::pair<float, float>(0, MOVE_VALUE), std::pair<float, float>(0, -MOVE_VALUE)};

    for (int i = 0; i < 4; i++) {
        std::shared_ptr<Entity> newEnemy(new Entity);
        newEnemy->x = width.at(i);
        newEnemy->y = height.at(i);
        newEnemy->spritePath = std::string("assets/solarfox/Opponent.png");
        newEnemy->orientation = orientation.at(i);
        newEnemy->backgroundColor = {29, 0, 255, 1};
        newEnemy->type = ENEMY;
        _enemies.emplace_back(newEnemy, moveCoor.at(i));
        _entities.emplace_back(newEnemy);
    }
}

void Solarfox::moveEnemies()
{
    /* HAUT, BAS, GAUCHE, DROITE */
    for (int i = 0; i < 2; i++) {
        if ((_enemies.at(i).first->x + _enemies.at(i).second.first >
             _mapWidth && _enemies.at(i).second.first > 0) ||
            (_enemies.at(i).first->x - _enemies.at(i).second.first < 0 &&
                _enemies.at(i).second.first < 0))
            _enemies.at(i).second.first = -(_enemies.at(i).second.first);
        _enemies.at(i).first->x += _enemies.at(i).second.first;
    }
    for (int i = 2; i < 4; i++) {
        if ((_enemies.at(i).first->y + _enemies.at(i).second.second >
             _mapHeight && _enemies.at(i).second.second > 0) ||
            (_enemies.at(i).first->y - _enemies.at(i).second.second < 0 &&
                _enemies.at(i).second.second < 0))
            _enemies.at(i).second.second = -(_enemies.at(i).second.second);
        _enemies.at(i).first->y += _enemies.at(i).second.second;
    }
}

bool Solarfox::moveDelay()
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

void Solarfox::initControls()
{
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::DOWN)] = [this](){
        Solarfox::moveDown();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::UP)] = [this](){
        Solarfox::moveUp();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::RIGHT)] = [this](){
        Solarfox::moveRight();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::LEFT)] = [this](){
        Solarfox::moveLeft();
    };
    _controls[std::pair<Event::Type, Event::Key>(Event::KEY_PRESSED, Event::S)] = [this](){
        Solarfox::createShootPlayer();
    };
}

void Solarfox::moveDown()
{
    if (_player.second.second == static_cast<float>(-MOVE_VALUE))
        return;

    _started = true;
    _player.first->x = std::round(_player.first->x);
    _player.second.first = 0;
    _player.second.second = MOVE_VALUE;
}

void Solarfox::moveUp()
{
    if (_player.second.second == static_cast<float>(MOVE_VALUE))
        return;
    _started = true;
    _player.first->x = std::round(_player.first->x);
    _player.second.first = 0;
    _player.second.second = -MOVE_VALUE;
}

void Solarfox::moveRight()
{
    if (_player.second.first == static_cast<float>(-MOVE_VALUE))
        return;
    _started = true;
    _player.first->y = std::round(_player.first->y);
    _player.second.first = MOVE_VALUE;
    _player.second.second = 0;
}

void Solarfox::moveLeft()
{
    if (_player.second.first == static_cast<float>(MOVE_VALUE))
        return;
    _started = true;
    _player.first->y = std::round(_player.first->y);
    _player.second.first = -MOVE_VALUE;
    _player.second.second = 0;
}

void Solarfox::movePlayer()
{
    _player.first->x += _player.second.first;
    _player.first->y += _player.second.second;
}

void Solarfox::createShootPlayer()
{
    if (!_shootsPlayer.empty())
        return;
    std::shared_ptr<Shoot> newShoot(new Shoot);
    newShoot->_shoot = std::make_shared<Entity>();
    newShoot->_shoot->spritePath = "assets/solarfox/FirePlayer.png";
    newShoot->_shoot->orientation = _player.first->orientation;
    newShoot->_shoot->backgroundColor = {95, 218, 222, 1};
    newShoot->_shoot->type = OTHER;
    newShoot->_shoot->x = _player.first->x + _player.second.first;
    newShoot->_shoot->y = _player.first->y + _player.second.second;
    newShoot->_move.first = _player.second.first * 4;
    newShoot->_move.second = _player.second.second * 4;
    newShoot->_origin.first = _player.first->x;
    newShoot->_origin.second = _player.first->y;
    _shootsPlayer.emplace_back(newShoot);
    _entities.emplace_back(newShoot->_shoot);
}

void Solarfox::createShootEnemy()
{
    /* HAUT BAS GAUCHE DROITE */
    int random = 0;
    std::vector<float> moveCorsX = {MOVE_VALUE, -MOVE_VALUE, 0, 0};
    std::vector<float> moveCorsY = {0, 0, MOVE_VALUE, -MOVE_VALUE};
    for (int i = 0; i < 4; i++) {
        random = rand() % 400;
        if (random) continue;
        std::shared_ptr<Shoot> newShoot(new Shoot);
        newShoot->_shoot = std::make_shared<Entity>();
        newShoot->_shoot->spritePath = "assets/solarfox/FireEnemy.png";
        newShoot->_shoot->orientation = _enemies.at(i).first->orientation;
        newShoot->_shoot->backgroundColor = {255, 182, 0, 1};
        newShoot->_shoot->type = OTHER;
        newShoot->_shoot->x = std::round(_enemies.at(i).first->x);
        newShoot->_shoot->y = std::round(_enemies.at(i).first->y);
        newShoot->_move.first = moveCorsY.at(i);
        newShoot->_move.second = moveCorsX.at(i);
        newShoot->_origin.first = std::round(_enemies.at(i).first->x);
        newShoot->_origin.second = std::round(_enemies.at(i).first->y);
        _shootsEnemies.emplace_back(newShoot);
        _entities.emplace_back(newShoot->_shoot);
    }
}

void Solarfox::moveShootsPlayer()
{
    for (const std::shared_ptr<Shoot> &sh : _shootsPlayer) {
        sh->_shoot->x += sh->_move.first;
        sh->_shoot->y += sh->_move.second;
        /*
        if (sh->_shoot->x > sh->_origin.first + 4 || sh->_shoot->x < sh->_origin.first - 4 || sh->_shoot->y > sh->_origin.second + 4 || sh->_shoot->y < sh->_origin.second - 4) {
            _entities.erase(std::remove(_entities.begin(), _entities.end(), sh->_shoot));
            _shootsPlayer.erase(std::remove(_shootsPlayer.begin(), _shootsPlayer.end(), sh));
        }
         */
    }
}

void Solarfox::moveShootsEnemy()
{
    for (const std::shared_ptr<Shoot> &sh : _shootsEnemies) {
        sh->_shoot->x += sh->_move.first;
        sh->_shoot->y += sh->_move.second;
        /*
        if (sh->_shoot->x > _mapWidth || sh->_shoot->x < 0 || sh->_shoot->y > _mapHeight || sh->_shoot->y < 0) {
            _entities.erase(std::remove(_entities.begin(), _entities.end(), sh->_shoot));
            _shootsPlayer.erase(std::remove(_shootsPlayer.begin(), _shootsPlayer.end(), sh));
        }
        if (sh->_shoot->x == _shootsPlayer.at(0)->_shoot->x && sh->_shoot->y == _shootsPlayer.at(0)->_shoot->y) {
            _entities.erase(std::remove(_entities.begin(), _entities.end(), sh->_shoot));
            _shootsPlayer.erase(std::remove(_shootsPlayer.begin(), _shootsPlayer.end(), sh));
        }
        if (sh->_shoot->x == _player.first->x && sh->_shoot->y == _player.first->y) {
            _gameOver = true;
            return;
        }
         */
    }
}

bool Shoot::operator==(const Shoot &rhs) const {
    return _shoot == rhs._shoot;
}

bool Shoot::operator!=(const Shoot &rhs) const {
    return !(rhs == *this);
}
