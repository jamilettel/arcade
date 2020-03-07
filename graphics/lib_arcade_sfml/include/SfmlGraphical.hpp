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

namespace arc {

    class SfmlGraphical: public IGraphical {
    public:

        SfmlGraphical();
        ~SfmlGraphical() = default;

        void display();
        Event::Type getEventType() const;
        Event::Key getKeyPressed() const;
        size_t getScreenWidth() const;
        size_t getScreenHeight() const;

        void setScene(Scene scene);
        Scene getScene() const;

        void setMainMenuOptions(const std::map<std::string, std::function<void()>> &mainMenu);
        void setPauseMenuOptions(const std::map<std::string, std::function<void()>> &pauseMenu);
        void setList(const std::vector<std::string> &list);
        void setGetInputMessage(const std::string &message);
        void setEndGameMessage(const std::string &message);
        void updateGameInfo(const std::vector<std::vector<char>> &gameMap);

        const std::string &getInput() const;

        void setSprites(const std::map<char, std::string> &sprites);
        void setBackgroundColors(const std::map<char, Color> &sprites);
        void setFont(const std::string &font);

        void setGameStatsFormatString(const std::string &info);
        void setHowToPlayFormatString(const std::string &info);

    private:
        void checkEvents();

        sf::RenderWindow _window;
        sf::Event _event;
        Event::Type _eventType;
        Event::Key _keyPressed;
        Scene _scene;

        std::map<std::string, std::function<void()>> _mainMenuOptions;
        std::map<std::string, std::function<void()>> _pauseMenuOptions;
        std::vector<std::string> _list;
        std::string _getInputMessage;
        std::string _endGameMessage;
        const std::vector<std::vector<char>> *_gameMap;

        std::string _input;

        std::map<char, sf::Sprite> _sprites;
        std::map<char, sf::Texture> _textures;

        sf::Font _font;
        sf::Text _text;

        std::string _gameStats;
        std::string _howToPlay;

    };

}

#endif /* SFML_GRAPHICAL_HPP_ */
