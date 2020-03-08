/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_NIBBLER_H
#define OOP_ARCADE_2019_NIBBLER_H

#include "IGame.hpp"

#define ROWS_SNAKE 20
#define COLS_SNAKE 20

namespace arc {

    class Nibbler : public IGame {
    public:
        Nibbler();
        ~Nibbler() override;

        const std::map<char, std::string> &getSprites() const override;
        const std::map<char, Color> &getBackgroundColors() const override;
        const std::string &getGameControlsFormatString() const override;

        void restart() override;
        void updateGame(Event::Type type, Event::Key keyPressed) override;

        const std::vector<std::vector<char>> &getMap() const override;
        const std::string &getGameStatsFormatString() const override;

    private:
        std::vector<std::vector<char>> _map;
        std::map<char, std::string> _sprites;
        std::map<char, Color> _backgroundColors;
        std::string _gameControlsFormatString;
        std::string _gameStatsFormatString;

        void mapCreation();
        void spritesCreation();
        void backgroundColorsCreation();
    };
}
#endif //OOP_ARCADE_2019_NIBBLER_H
