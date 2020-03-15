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
        Event::Type getEventType() const override;
        Event::Key getKeyPressed() const override;

        void setListGames(const std::vector<std::string> &games, const std::function<void (const std::string &)> &fct, int chosen = -1) override;
        void setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen = -1) override;
        void setScores(const std::vector<std::pair<std::string, std::string>> &scores) override;

        void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls) override;

        void setFunctionPlay(const std::function<void()> &function) override;
        void setFunctionRestart(const std::function<void()> &function) override;
        void setFunctionMenu(const std::function<void()> &function) override;
        void setFunctionTogglePause(const std::function<void()> &function) override;

        const std::string &getUsername() override;
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

    public:
        void checkEvents();
        std::optional<std::vector<std::pair<std::string, std::string>>> &getHowToPlay();
    private:
        Event::Type _eventType;
        Event::Key _keyPressed;
        std::vector<std::pair<std::string,std::string>> _scores;
        std::optional<const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>>> _controlsMap;
        Scene _scene;
        std::string _username;
        std::string _gameTitle;
        std::optional<std::vector<std::pair<std::string, std::string>>> _controlsString;

    private:
        /* COLORS */
        bool supportColor() const;
        void initColor() const;
    private:
        std::map<Scene, std::shared_ptr<IScene>> _sceneList;
        bool _termColor;
        static const std::map<int, Event::Key> _equivalentKeys;

    };

    enum COLOR_PAIR
    {
        GREEN_BLACK = 1,
        RED_BLACK,
        BLACK_BLUE,
        GREEN_BLUE,
        RED_BLUE,
        RED_WHITE,
        YELLOW_BLUE,
    };
}

#endif //OOP_ARCADE_2019_NCURSESGRAPHICAL_HPP
