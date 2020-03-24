/*
** EPITECH PROJECT, 2020
** MySDL
** File description:
** List
*/

#ifndef MYSF_ILIST_HPP_
#define MYSF_ILIST_HPP_

#include "MySDL/Window.hpp"
#include "MySDL/Rectangle.hpp"
#include "MySDL/Text.hpp"
#include <string>
#include <vector>

namespace MySDL {

    class IList {
    public:

        virtual ~IList() = default;

        virtual void setList(const std::vector<std::string> &list) = 0;
        virtual const std::vector<std::string> &getList() const = 0;
        virtual const std::string getTitle() const = 0;
        virtual void setTitle(const std::string &title) = 0;

        virtual const MySDL::Font &getFont() const = 0;
        virtual MySDL::Font &getFont() = 0;

        virtual void draw() = 0;
        virtual void drawElement(size_t element, const MySDL::Vector &pos) = 0;

        virtual void setSize(const MySDL::Vector &size) = 0;
        virtual void setPos(const MySDL::Vector &pos) = 0;
        virtual const MySDL::Vector &getSize() const = 0;
        virtual const MySDL::Vector &getPos() const = 0;

    };

}

#endif /* MYSF_ILIST_HPP) */
