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
                GAME,
                END_GAME,
            };

            virtual ~IGraphical() = default;

            virtual void display() = 0;
            virtual Event::Type getEventType() = 0;
            virtual Event::Key getKeyPressed() const = 0;

            virtual void setListGames(const std::vector<std::string> &games, const std::function<void (const std::string &)> &fct, int chosen = -1) = 0;
            virtual void setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen = -1) = 0;
            virtual void setScores(const std::vector<std::pair<std::string, std::string>> &scores) = 0;

            virtual void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls) = 0;

            virtual void setFunctionPlay(const std::function<void()> &function) = 0;
            virtual void setFunctionRestart(const std::function<void()> &function) = 0;
            virtual void setFunctionMenu(const std::function<void()> &function) = 0;
            virtual void setFunctionTogglePause(const std::function<void()> &function) = 0;

            virtual const std::string &getUsername() const = 0;
            virtual Scene getScene() const = 0;
            virtual void setScene(Scene scene) = 0;

            virtual void setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info) = 0;
            virtual void setGameStatsFormatString(const std::vector<std::string> &info) = 0;
            virtual void setFont(const std::string &font) = 0;
            virtual void setVisualAssets(const std::map<char, std::pair<std::string, Color>> &sprites) = 0;
            virtual void updateGameInfo(const std::vector<Entity> &gameMap) = 0;
            virtual void setMusic(const std::string &music) = 0;
            virtual void playSound(const std::string &sound) = 0;

            virtual void setMapSize(size_t height, size_t width) = 0;
    };
}

#endif /* IGRAPHICAL_HPP_ */
