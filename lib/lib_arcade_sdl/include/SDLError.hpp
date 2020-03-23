/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML Error
*/

#ifndef SFML_ERROR_HPP_
#define SFML_ERROR_HPP_

#include "Error.hpp"

namespace arc {

    class SDLError: public ArcadeError {
    public:
        SDLError(const std::string &message);
    };

}

#endif /* SFML_ERROR_HPP_ */
