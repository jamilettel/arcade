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
#include "DLLoader.hpp"

#define GAME_DIR "games/"

#define GRAPHICAL_DIR "lib/"

namespace arc {

    class Core {
    public:
        Core(const std::string &graphicalLib);
        ~Core();

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

        static std::string getDynamicLibraryName(const std::string &path);

        void setCurrentLib(const std::string &lib);
        void setCurrentGame(const std::string &game);

        void sendListsToGraphicalLib();

        void initGeneralControl();

        std::unique_ptr<IGraphical> _graphical;
        std::unique_ptr<IGraphical> _oldGraphical;
        std::unique_ptr<IGame> _game;
        std::unique_ptr<IGame> _oldGame;

        std::string _currentGame;
        std::vector<std::string> _gameList;
        std::map<std::string, std::unique_ptr<DLLoader<IGame>>> _gameLoaders;

        std::string _currentGraphicalLib;
        std::vector<std::string> _graphicalList;
        std::map<std::string, std::unique_ptr<DLLoader<IGraphical>>> _graphicalLoaders;

        bool _quitGame;
        bool _isPaused;

        IGraphical::Scene _scene;

        std::map<Event::Key, std::function<void ()>> _generalControls;

    };

}

#endif /* CORE_HPP_ */
