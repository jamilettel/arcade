/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IGame
*/

/**
 * \file        IGame.hpp
 * \author      Benjamin Bourgeois - Jamil Ettel
 * \version     2.0
 * \date        March 8 2020
 * \brief       Define the IGame interface
 * \details     This interface is used by the core to interact with all games. Core will not call method which are not in IGame
 */

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "Utils.hpp"
#include <vector>
#include <map>
#include <functional>
#include <memory>

namespace arc {
    /**
     * \class IGame
     * \brief This interface is the link between a game and the core. All games must derived from this interface and implement all methods
     */
    class IGame {
    public:
        /**
         *  \brief Destructor
         */
        virtual ~IGame() = default;
        /*!
         *  \brief Getter for the height of the map
         *  \return Height of the map
         */
        virtual size_t getMapHeight() const = 0;
        /*!
         *  \brief Getter for the width of the map
         *  \return Width of the map
         */
        virtual size_t getMapWidth() const = 0;
        virtual const std::string &getMusic() const = 0;
        virtual const std::string &getSound() const = 0;
        virtual const std::string &getScore() = 0;
        virtual const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &getControls() const = 0;

        virtual const std::vector<std::shared_ptr<Entity>> &getEntities() const = 0;

        virtual const std::vector<std::pair<std::string, std::string>> &getGameControls() const = 0;
        virtual const std::vector<std::pair<std::string, std::string>> &getGameStats() const = 0;

        /*!
         *  \brief Call this function to restart the entire game. The game must reset himself.
         */
        virtual void restart() = 0;
        virtual void updateGame() = 0;
        /*!
         *  \brief Check if the game is over
         *  \return bool which indicate if the game is over
         */
        virtual bool isGameOver() const = 0;
        /*!
         *  \brief Get the name of the game
         *  \return Name of the game
         */
        virtual const std::string &getTitle() const = 0;
    };
}

#endif /* IGAME_HPP_ */
