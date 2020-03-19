/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** Error
*/

#ifndef MYSF_ERROR_HPP_
#define MYSF_ERROR_HPP_

#include <exception>
#include <string>

namespace MySf {

    class Error: public std::exception {
    public:
        Error(const std::string &component, const std::string &message);

        const char *what() const noexcept override;
        const std::string &getComponent() const noexcept;

    protected:
        std::string _component;
        std::string _message;
    };

}

#endif /* MYSF_ERROR_HPP_ */
