/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** Error
*/

#ifndef COREERROR_HPP_
#define COREERROR_HPP_

#include <exception>
#include <string>
#include "Error.hpp"

namespace arc {

    class DLLoaderError: public ArcadeError {
    public:
        DLLoaderError(const std::string &message);
    };

}
#endif /* COREERROR_HPP_ */
