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

#define BUTTON_COLOR MySf::Button::TriColor(sf::Color(0x416C99FF),\
                                            sf::Color(0x5B95D4FF),\
                                            sf::Color::White)

#define TEXT_COLOR MySf::Button::TriColor(sf::Color::White,\
                                          sf::Color::White,\
                                          sf::Color(0x5B95D4FF))

namespace arc {

    class SfmlGraphical: public IGraphical {
    public:

        SfmlGraphical();
        ~SfmlGraphical() = default;

        void display();
        Event::Type getEventType();
        Event::Key getKeyPressed() const;

        void setListGames(const std::vector<std::string> &games,
                          const std::function<void (const std::string &)> &fct,
                          int chosen = -1);
        void setListLibraries(const std::vector<std::string> &libraries,
                              const std::function<void (const std::string &)> &fct,
                              int chosen = -1);
        void setScores(const std::vector<std::pair<std::string, std::string>> &scores);
        void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls);

        void setFunctionPlay(const std::function<void()> &function);
        void setFunctionRestart(const std::function<void()> &function);
        void setFunctionMenu(const std::function<void()> &function);
        void setFunctionTogglePause(const std::function<void()> &function);

        const std::string &getUsername() const;
        Scene getScene() const;
        void setScene(Scene scene);

        void setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info);
        void setGameStatsFormatString(const std::vector<std::string> &info);
        void setFont(const std::string &font);
        void setSprites(const std::map<char, std::string> &sprites);
        void setBackgroundColors(const std::map<char, Color> &sprites);
        void updateGameInfo(const std::vector<Entity> &gameMap);
        void setMusic(const std::string &music);
        void playSound(const std::string &sound);

        void setMapSize(size_t height, size_t width);

    private:
        void checkEvents();

        sf::RenderWindow _window;
        sf::Event _event;
        Event::Type _eventType;
        Event::Key _keyPressed;
        Scene _scene;
        std::string _username;

        std::vector<std::string> _list;
        std::string _getInputMessage;
        std::string _endGameMessage;
        std::vector<Entity> _gameMap;

        std::string _input;

        std::map<char, sf::Sprite> _sprites;
        std::map<char, sf::Texture> _textures;
        std::map<char, std::string> _spriteMap;

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

        const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> *_controlsMap;

        sf::Music _music;

    };

}

#endif /* SFML_GRAPHICAL_HPP_ */
