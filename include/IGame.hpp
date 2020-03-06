/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_


#include "Utils.hpp"
#include <vector>
#include <map>

namespace arc {

    class IGame {
    public:
        virtual ~IGame() = 0;

        virtual const std::map<char, std::string> &getSprites() const = 0;
        virtual const std::map<char, Color> &getBackgroundColors() const = 0;
        virtual const std::string &getGameControlsFormatString() const = 0;

        virtual void restart() = 0;
        virtual void updateGame(Event::Type type, Event::Key keyPressed) = 0;

        virtual const std::vector<std::vector<char>> &getMap() const = 0;
        virtual const std::string &getGameStatsFormatString() const = 0;

    };

}

#endif /* IGAME_HPP_ */
