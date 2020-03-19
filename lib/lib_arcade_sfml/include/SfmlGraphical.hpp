/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML Graphical header file
*/

#ifndef SFML_GRAPHICAL_HPP_
#define SFML_GRAPHICAL_HPP_

#include "Scene/IScene.hpp"
#include "MySf/InputZone.hpp"
#include "IGraphical.hpp"
#include <SFML/Graphics.hpp>
#include "MySf/Button/RectButton.hpp"
#include <SFML/Audio.hpp>

#define BUTTON_COLOR MySf::Button::ButtonColor(sf::Color(0x0a0a0aff),\
                                               sf::Color(0x131313ff),\
                                               sf::Color(0x5f5f5fff),\
                                               sf::Color(0x343434ff))

#define TEXT_COLOR MySf::Button::ButtonColor(sf::Color::White,\
                                             sf::Color::White,\
                                             sf::Color::White,\
                                             sf::Color(0x777777ff))

namespace arc {

    class SfmlGraphical: public IGraphical {
    public:

        SfmlGraphical();
        ~SfmlGraphical() = default;

        void display() override;
        Event::Type getEventType() const override;
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

        const std::string &getUsername() override;
        void setUsername(const std::string &name) override;

        Scene getScene() const override;
        void setScene(Scene scene) override;

        void setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info) override;
        void setGameStats(const std::vector<std::string> &info) override;
        void setFont(const std::string &font) override;
        void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap) override;

        void setMapSize(size_t height, size_t width) override;
        void setGameTitle(const std::string &game) override;

        sf::Sprite &getSprite(const std::string &sprite, const sf::Vector2f &size,
                              const Color &color);

    private:
        void checkEvents();
        void loadSprite(const std::string &spritePath, const Color &color);

        static void setSpriteSize(sf::Sprite &sprite, const sf::Vector2f &size);

        sf::RenderWindow _window;
        sf::Event _event;
        Event::Type _eventType;
        Event::Key _keyPressed;
        Scene _scene;

        std::map<Scene, std::unique_ptr<IScene>> _scenes;

        std::map<std::string, sf::Sprite> _sprites;
        std::map<std::string, sf:: Texture> _textures;
        std::map<char, std::pair<std::string, Color>> _spriteMap;

        sf::Font _font;

        sf::Music _music;
        static const std::map<sf::Keyboard::Key, Event::Key> _equivalentKeys;

    };

}

#endif /* SFML_GRAPHICAL_HPP_ */
