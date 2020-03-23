/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML Error
*/

#ifndef SOLARFOX_ERROR_HPP_
#define SOLARFOX_ERROR_HPP_

#include "Error.hpp"

namespace arc {

    class SolarfoxError: public ArcadeError {
    public:
        SolarfoxError(const std::string &message);
    };

}

#endif /* SOLARFOX_ERROR_HPP_ */
