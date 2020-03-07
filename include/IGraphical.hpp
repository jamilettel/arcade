/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL_HPP_
#define IGRAPHICAL_HPP_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include "Utils.hpp"

namespace arc {

    class IGraphical {
    public:

        enum Scene {
            MAIN_MENU,
            PAUSE_MENU,
            GAME,
            END_GAME,
            LIST,
            HOW_TO_PLAY,
            GET_INPUT,
        };

        virtual ~IGraphical() = 0;

        virtual void display() = 0;
        virtual Event::Type getEventType() const = 0;
        virtual Event::Key getKeyPressed() const = 0;
        virtual size_t getScreenWidth() const = 0;
        virtual size_t getScreenHeight() const = 0;

        virtual void setScene(Scene scene) = 0;
        virtual Scene getScene() const = 0;

        virtual void setMainMenuOptions(const std::map<std::string, std::function<void()>> &mainMenu) = 0;
        virtual void setPauseMenuOptions(const std::map<std::string, std::function<void()>> &pauseMenu) = 0;
        virtual void setList(const std::vector<std::string> &list) = 0;
        virtual void setGetInputMessage(const std::string &message) = 0;
        virtual void setEndGameMessage(const std::string &message) = 0;
        virtual void updateGameInfo(const std::vector<std::vector<char>> &gameMap) = 0;

        virtual const std::string &getInput() const = 0;

        virtual void setSprites(const std::map<char, std::string> &sprites) = 0;
        virtual void setBackgroundColors(const std::map<char, Color> &sprites) = 0;
        virtual void setFont(const std::string &font) = 0;

        virtual void setGameStatsFormatString(const std::string &info) = 0;
        virtual void setHowToPlayFormatString(const std::string &info) = 0;

    };

}

#endif /* IGRAPHICAL_HPP_ */
