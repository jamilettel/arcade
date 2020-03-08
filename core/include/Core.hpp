/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include "IGraphical.hpp"
#include "IGame.hpp"

#define GAME_DIR "games/"

#define GRAPHICAL_DIR "graphics/"

namespace arc {

    class Core {
    public:
        Core(const std::string &graphicalLib);

        void loadGraphicalLibrary(const std::string &path);
        void loadGameLibrary(const std::string &path);

        void run();

        std::vector<std::pair<std::string, std::string>> getControls() const;

    private:
        void refreshLibrarieLists();
        const std::vector<std::string> &getGameList() const;
        const std::vector<std::string> &getGraphicalList() const;

        void setGraphicalLibFunctions();
        void startGame();

        std::unique_ptr<IGraphical> _graphical;
        std::unique_ptr<IGame> _game;

        std::string _currentGame;
        std::vector<std::string> _gameList;
        std::string _currentGraphicalLib;
        std::vector<std::string> _graphicalList;

        bool _quitGame;
        bool _isPaused;

    };

}

#endif /* CORE_HPP_ */
