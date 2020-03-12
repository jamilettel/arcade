/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** NCURSES Error
*/

#ifndef NCURSES_ERROR_HPP_
#define NCURSES_ERROR_HPP_

#include "Error.hpp"

namespace arc {

    class NcursesError: public ArcadeError {
    public:
        NcursesError(const std::string &message);
    };

}

#endif /* SFML_ERROR_HPP_ */
