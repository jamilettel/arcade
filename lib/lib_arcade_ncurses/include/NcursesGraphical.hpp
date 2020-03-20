/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_NCURSESGRAPHICAL_HPP
#define OOP_ARCADE_2019_NCURSESGRAPHICAL_HPP

#include "IGraphical.hpp"
#include "IScene.hpp"
#include <ncurses.h>

namespace arc {

    class NcursesGraphical : public IGraphical {
    public:
        NcursesGraphical();
        ~NcursesGraphical() override;

        void display() override;
        [[nodiscard]] Event::Type getEventType() const override;
        [[nodiscard]] Event::Key getKeyPressed() const override;

        void setListGames(const std::vector<std::string> &games, const std::function<void (const std::string &)> &fct, int chosen = -1) override;
        void setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen = -1) override;
        void setScores(const std::vector<std::pair<std::string, std::string>> &scores) override;

        void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls) override;

        void setFunctionPlay(const std::function<void()> &function) override;
        void setFunctionRestart(const std::function<void()> &function) override;
        void setFunctionMenu(const std::function<void()> &function) override;
        void setFunctionTogglePause(const std::function<void()> &function) override;

        const std::string &getUsername() override;
        void setUsername(const std::string &username) override;
        [[nodiscard]] Scene getScene() const override;
        void setScene(Scene scene) override;

        void setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info) override;
        void setGameStats(const std::vector<std::pair<std::string, std::string>> &info) override;
        void setFont(const std::string &font) override;
        void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap) override;

        void setMapSize(size_t height, size_t width) override;
        void setGameTitle(const std::string &game) override;

    public:
        void checkEvents();
        std::optional<std::vector<std::pair<std::string, std::string>>> &getHowToPlay();
    private:
        Event::Type _eventType;
        Event::Key _keyPressed;
        Scene _scene;
        std::string _username;
        std::optional<std::vector<std::pair<std::string, std::string>>> _controlsString;
    public:
        std::optional<std::function<void()>> _playFct;
        std::optional<std::function<void()>> _restartFct;
        std::optional<std::function<void()>> _menuFct;
        std::optional<std::function<void()>> _pauseFct;

    public:
        void addColor(Color color);
        short getColor(Color color);
        void initPairColor(short color1, short color2);
        short getPairColor(short color1, short color2);

    private:
        /* COLORS */
        bool supportColor() const;
    private:
        std::map<Scene, std::shared_ptr<IScene>> _sceneList;
        bool _termColor;
        static const std::map<int, Event::Key> _equivalentKeys;
        std::map<Color, short> _colorIndex;
        std::map<std::pair<short, short>, short> _pairColorIndex;

    };
}

#endif //OOP_ARCADE_2019_NCURSESGRAPHICAL_HPP
