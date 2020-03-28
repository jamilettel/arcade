/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** GameScene
*/

#ifndef GAMESCENE_SCENE_HPP_
#define GAMESCENE_SCENE_HPP_

#include "Scene/IScene.hpp"
#include "Button/RectButton.hpp"
#include "Utils.hpp"
#include "SDLGraphical.hpp"
#include "List/BasicList.hpp"

namespace arc {

    class GameScene: public IScene {
    public:
        GameScene(MySDL::Window &window, MySDL::Font &font, SDLGraphical &lib);

        void draw() override;
        void drawPaused();
        void update(const SDL_Event &event) override;

        void setMapSize(size_t height, size_t width);

        void setGameTitle(const std::string &title);

        void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap);

        void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls);

        void setGameStats(const std::vector<std::pair<std::string, std::string>> &stats);
        const std::vector<std::string> &getGameStats() const;

        void setFunctionTogglePause(const std::function<void()> &function);
        void setFunctionMenu(const std::function<void()> &function);
        void setFunctionRestart(const std::function<void()> &function);

        void setHowToPlay(const std::vector<std::pair<std::string,std::string>> &info);
        void setPause(bool status);

    private:

        SDLGraphical &_lib;
        MySDL::Window &_window;
        MySDL::Font &_font;

        static const SDL_FRect _gameArea;
        MySDL::Rectangle _gameBackground;
        MySDL::Text _gameTitle;

        std::optional<MySDL::Button::RectButton> _pause;
        std::optional<MySDL::Button::RectButton> _resume;
        std::optional<MySDL::Button::RectButton> _menu;
        std::optional<MySDL::Button::RectButton> _restart;
        std::optional<std::vector<std::shared_ptr<Entity>>> _gameMap;

        float _cellHeight;
        float _cellWidth;

        std::optional<const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>>> _controlsMap;

        std::vector<std::string> _gameStatList;
        MySDL::BasicList _gameStats;

        bool _paused;

        MySDL::Rectangle _pauseRect;
        SDL_Color _pauseColorTarget;
        MySDL::Color::SmoothShifting _pauseRectColor;

        std::optional<MySDL::BasicList> _howToPlay;
        std::vector<std::string> _howToPlayDesc;
        std::vector<std::string> _howToPlayKeys;

        std::string _username;
        MySDL::Text _userText;

    };

}

#endif /* GAMESCENE_SCENE_HPP_ */
