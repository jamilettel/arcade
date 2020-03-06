/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <string>

namespace arc {

    class ArcadeError: public std::exception {
    public:
        ArcadeError(const std::string &component, const std::string &message);

        const char *what() const noexcept override;
        const std::string &getComponent() const noexcept;

    private:
        std::string _component;
        std::string _message;
    };

}
#endif /* ERROR_HPP_ */
