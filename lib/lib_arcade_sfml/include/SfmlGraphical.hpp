/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML Graphical header file
*/

#ifndef SFML_GRAPHICAL_HPP_
#define SFML_GRAPHICAL_HPP_

#include "IGraphical.hpp"
#include <SFML/Graphics.hpp>
#include "Button/RectButton.hpp"
#include <SFML/Audio.hpp>

#define BUTTON_COLOR MySf::Button::ButtonColor(sf::Color(0x416C99FF),\
                                               sf::Color(0x5B95D4FF),\
                                               sf::Color::White,\
                                               sf::Color(0x444444ff))

#define TEXT_COLOR MySf::Button::ButtonColor(sf::Color::White,\
                                             sf::Color::White,\
                                             sf::Color(0x5B95D4FF),\
                                             sf::Color(0xbbbbbbff))

namespace arc {

    class SfmlGraphical: public IGraphical {
    public:

        SfmlGraphical();
        ~SfmlGraphical() = default;

        void display() override;
        Event::Type getEventType() override;
        Event::Key getKeyPressed() const override;

        void setListGames(const std::vector<std::string> &games,
                          const std::function<void (const std::string &)> &fct,
                          int chosen = -1) override;
        void setListLibraries(const std::vector<std::string> &libraries,
                              const std::function<void (const std::string &)> &fct,
                              int chosen = -1) override;
        void setScores(const std::vector<std::pair<std::string, std::string>> &scores) override;
        void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls) override;

        void setFunctionPlay(const std::function<void()> &function) override;
        void setFunctionRestart(const std::function<void()> &function) override;
        void setFunctionMenu(const std::function<void()> &function) override;
        void setFunctionTogglePause(const std::function<void()> &function) override;

        const std::string &getUsername() const override;
        Scene getScene() const override;
        void setScene(Scene scene) override;

        void setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info) override;
        void setGameStatsFormatString(const std::vector<std::string> &info) override;
        void setFont(const std::string &font) override;
        void setVisualAssets(const std::map<char, std::pair<std::string, Color>> &sprites) override;
        void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap) override;
        void setMusic(const std::string &music) override;
        void playSound(const std::string &sound) override;

        void setMapSize(size_t height, size_t width) override;
        void setGameTitle(const std::string &game) override;

    private:
        void checkEvents();
        void checkGameEvents();
        void displayGame();
        void loadSprite(const std::string &spritePath);

        void createMainMenuButtons();

        void setSpriteScales();

        sf::RenderWindow _window;
        sf::Event _event;
        Event::Type _eventType;
        Event::Key _keyPressed;
        Scene _scene;
        std::string _username;

        std::vector<std::string> _list;
        std::string _getInputMessage;
        std::string _endGameMessage;
        std::optional<std::vector<std::shared_ptr<Entity>>> _gameMap;

        std::string _input;

        std::map<std::string, sf::Sprite> _sprites;
        std::map<std::string, sf:: Texture> _textures;
        std::map<char, std::pair<std::string, Color>> _spriteMap;

        sf::Font _font;
        sf::Text _text;

        std::vector<std::string> _gameStats;
        std::vector<std::pair<std::string, std::string>> _controls;

        std::vector<std::pair<std::string,std::string>> _scores;

        std::vector<std::unique_ptr<MySf::Button::IButton>> _mainMenuButtons;
        std::vector<std::unique_ptr<MySf::Button::IButton>> _pauseMenuButtons;

        std::unique_ptr<MySf::Button::IButton> _pauseButton;

        std::vector<std::unique_ptr<MySf::Button::IButton>> _gamesList;
        std::function<void (const std::string &)> _changeGameFct;

        size_t _mapHeight;
        size_t _mapWidth;

        static const sf::IntRect _gameArea;
        sf::Vector2f _cellSize;

        std::optional<const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>>> _controlsMap;

        sf::Music _music;

        static const std::map<sf::Keyboard::Key, Event::Key> _equivalentKeys;

        sf::Text _gameTitle;
        sf::RectangleShape _gameBackground;

    };

}

#endif /* SFML_GRAPHICAL_HPP_ */
