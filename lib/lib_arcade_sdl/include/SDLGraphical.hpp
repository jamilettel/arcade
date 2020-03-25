/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML Graphical header file
*/

#ifndef SFML_GRAPHICAL_HPP_
#define SFML_GRAPHICAL_HPP_

#include "Scene/IScene.hpp"
#include "InputZone.hpp"
#include "IGraphical.hpp"
#include "Button/RectButton.hpp"
#include "MySDL/Sprite.hpp"
#include "MySDL/Text.hpp"

#define BUTTON_COLOR MySDL::Button::ButtonColor(SDL_Color{0x0a, 0x0a, 0x0a, 0xff}, \
                                                SDL_Color{0x13, 0x13, 0x13, 0xff}, \
                                                SDL_Color{0x5f, 0x5f, 0x5f, 0xff}, \
                                                SDL_Color{0x34, 0x34, 0x34, 0xff})

#define TEXT_COLOR MySDL::Button::ButtonColor(SDL_Color{0xff, 0xff, 0xff, 0xff}, \
                                              SDL_Color{0xff, 0xff, 0xff, 0xff}, \
                                              SDL_Color{0xff, 0xff, 0xff, 0xff}, \
                                              SDL_Color{0x77, 0x77, 0x77, 0xff})

namespace arc {

    class SDLGraphical: public IGraphical {
    public:

        SDLGraphical();
        ~SDLGraphical() = default;

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
        void setGameStats(const std::vector<std::pair<std::string, std::string>> &info) override;
        void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap) override;

        void setMapSize(size_t height, size_t width) override;
        void setGameTitle(const std::string &game) override;

        MySDL::Sprite &getSprite(const std::string &sprite, const MySDL::Vector &size,
                              const Color &color);

        void setGamePause(bool pause) override;

    private:
        void checkEvents();
        void loadSprite(const std::string &spritePath, const Color &color);

        static void setSpriteSize(MySDL::Sprite &sprite, const MySDL::Vector &size);

        MySDL::Window _window;
        SDL_Event _event;
        Event::Type _eventType;
        Event::Key _keyPressed;
        Scene _scene;

        std::map<Scene, std::unique_ptr<IScene>> _scenes;

        std::map<std::string, MySDL::Sprite> _sprites;
        std::map<char, std::pair<std::string, Color>> _spriteMap;

        MySDL::Font _font;

        static const std::map<SDL_Scancode, Event::Key> _equivalentKeys;

    };

}

#endif /* SFML_GRAPHICAL_HPP_ */
