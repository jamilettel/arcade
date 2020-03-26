/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** Error
*/

/**
 * \file        Error.hpp
 * \author      Amaury Lecomte - Benjamin Bourgeois - Celeste Bousseau - Jamil Ettel - Oriane Aumoitte
 * \date        March 8 2020
 * \brief       Error Arcade program
 * \details     ArcadeError are used by the core to detect error.
 */

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <string>

namespace arc {
    /**
     * \class ArcadeError
     * \brief This class is the main error class in the Arcade program. All other class error must be derived from this class
     */
    class ArcadeError: public std::exception {
    public:
        /**
         *  \brief Constructor
         *  @param component Component's name in which the error appears
         *  @param message Error message
         */
        ArcadeError(const std::string &component, const std::string &message);

        /**
         *  \brief Get the error message
         *  @return Error message
         */
        const char *what() const noexcept override;
        /**
         *  \brief Get the name of the component in error
         *  @return Name of the component in error
         */
        const std::string &getComponent() const noexcept;

    private:
        /// Component's name in which the error appears.
        std::string _component;
        /// Error message.
        std::string _message;
    };

}
#endif /* ERROR_HPP_ */
