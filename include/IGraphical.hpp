/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IGraphical
*/

/**
 * \file        IGraphical.hpp
 * \author      Amaury Lecomte - Benjamin Bourgeois - Celeste Bousseau - Jamil Ettel - Oriane Aumoitte
 * \date        March 8 2020
 * \brief       Graphical interface
 * \details     Graphical modules are used by the core to interact with the player. These should be able to display menus, the game, and information about the game.
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

    /**
     * \class IGraphical
     * \brief Graphical interface
     * \details This class is used by the core to display information about the game and let the player interact with it.
     * \details You can implement a graphical library by creating a class that inherits from this one.
     * \details An extern "C" constructor 'IGraphical *instance_ctor();' is needed for the core to be able to load the class.
     */
    class IGraphical {
    public:

        enum Scene {
            /// You enter this scene when launching the arcade, it should display the scores of the chosen game,
            /// let you choose between graphical libraries and games, play the chosen game and exit the arcade.
            /// It is also possible to display the arcade controls in this scene. The player must be able to set
            /// and change his username in this scene
            MAIN_MENU,
            /// This is the game scene, it should display the game. It can display game information, buttons
            /// (restart, go to main menu, pause game) and the arcade and game controls.
            GAME,
            /// This scene is not mandatory, it can display the current score, previous high scores and give the option to the player to
            /// restart the game or return to the main menu.
            END_GAME,
        };

        virtual ~IGraphical() = default;

        /// This function must display the current scene. It is used in the game loop.
        virtual void display() = 0;

        /// This function must return the event type. It is called once per frame.
        virtual Event::Type getEventType() const = 0;

        /// This function must returns the key pressed, if any. It is also called once per frame.
        virtual Event::Key getKeyPressed() const = 0;

        /// The core provides a list of games to the user through this function. When a game is chosen from the list (first argument),
        /// it should be passed to the function (second argument). The third argument represents the currently chosen game, if any.
        /// If no game is chosen, it is set to -1.
        virtual void setListGames(const std::vector<std::string> &games, const std::function<void (const std::string &)> &fct, int chosen = -1) = 0;

        /// The core provides a list of libraries to the user through this function. When a library is chosen from the list (first argument),
        /// it should be passed to the function (second argument). The third argument represents the currently chosen library, if any.
        /// If no library is chosen, it is set to -1.
        virtual void setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen = -1) = 0;

        /// This function sets the list of scores. First element of the pair is the username, the second is the score.
        virtual void setScores(const std::vector<std::pair<std::string, std::string>> &scores) = 0;

        /// This function sets the controls for the game. They should be checked for only when the current scene is GAME.
        virtual void setControls(const std::map<std::pair<Event::Type, Event::Key>, std::function<void ()>> &controls) = 0;

        /// This is the function that lets the game start. Should only be called when a game is chosen.
        virtual void setFunctionPlay(const std::function<void()> &function) = 0;

        /// This function should be used in the GAME and END_GAME scenes. It restarts the game.
        virtual void setFunctionRestart(const std::function<void()> &function) = 0;

        /// This function should be used in the GAME and END_GAME scenes. It restarts the game.
        virtual void setFunctionMenu(const std::function<void()> &function) = 0;

        /// This function should be used to pause and unpause the game when it is running (GAME scene).
        virtual void setFunctionTogglePause(const std::function<void()> &function) = 0;

        /// Should return the username entered by the player in the main menu scene.
        virtual const std::string &getUsername() = 0;

        /// This function is called to set the username of the player in case he entered one earlier.
        virtual void setUsername(const std::string &username) = 0;

        /// Returns the current scene.
        virtual Scene getScene() const = 0;

        /// Sets the current scene.
        virtual void setScene(Scene scene) = 0;

        /// This is information for the player about the game controls. First element of the pair is the description of the action,
        /// the second is the key mapped to it.
        virtual void setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info) = 0;

        /// This is called in a loop when the game is running. Sets the current game information. The first element of the pair
        /// is the category (e.g. Score), the second is the value (e.g. 200).
        virtual void setGameStats(const std::vector<std::pair<std::string, std::string>> &info) = 0;

        /// This is called in a loop when the game is running. This vector contains entities that should be displayed in the game scene.
        virtual void updateGameInfo(const std::vector<std::shared_ptr<Entity>> &gameMap) = 0;

        /// Sets the size of the game map.
        virtual void setMapSize(size_t height, size_t width) = 0;

        /// Sets the title of the game.
        virtual void setGameTitle(const std::string &game) = 0;

        /// Informs the game library whether the game is paused or not. It is called when the library is loaded and when there is a change.
        virtual void setGamePause(bool pause) = 0;
    };
}

#endif /* IGRAPHICAL_HPP_ */
