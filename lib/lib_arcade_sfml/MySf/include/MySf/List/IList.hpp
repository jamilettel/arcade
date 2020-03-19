/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#ifndef MYSF_ILIST_HPP_
#define MYSF_ILIST_HPP_

#include <SFML/Graphics.hpp>

namespace MySf {

    class IList {
    public:

        virtual ~IList() = default;

        virtual void setList(const std::vector<std::string> &list) = 0;
        virtual const std::vector<std::string> &getList() const = 0;
        virtual const std::string getTitle() const = 0;
        virtual void setTitle(const std::string &title) = 0;

        virtual const sf::Font &getFont() const = 0;
        virtual sf::Font &getFont() = 0;

        virtual void draw() = 0;
        virtual void drawElement(size_t element, const sf::Vector2f &pos) = 0;

        virtual void setSize(const sf::Vector2f &size) = 0;
        virtual void setPos(const sf::Vector2f &pos) = 0;
        virtual const sf::Vector2f &getSize() const = 0;
        virtual const sf::Vector2f &getPos() const = 0;

    };

}

#endif /* MYSF_ILIST_HPP) */
