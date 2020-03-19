/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** AList
*/

#ifndef MYSF_ALIST_HPP_
#define MYSF_ALIST_HPP_

#include "MySf/List/IList.hpp"

namespace MySf {

    class AList: public IList {
    public:
        AList(sf::RenderWindow &window, sf::Font &font,
              const std::vector<std::string> &list,
              const std::string &title);

        virtual void setList(const std::vector<std::string> &list) override;
        virtual const std::vector<std::string> &getList() const override;
        virtual const std::string getTitle() const override;
        virtual void setTitle(const std::string &title) override;

        virtual const sf::Font &getFont() const override;
        virtual sf::Font &getFont() override;

        virtual void setSize(const sf::Vector2f &size) override;
        virtual void setPos(const sf::Vector2f &pos) override;
        virtual const sf::Vector2f &getSize() const override;
        virtual const sf::Vector2f &getPos() const override;

    protected:
        sf::RenderWindow &_window;
        sf::Font &_font;
        std::vector<std::string> _list;

        sf::Vector2f _pos;
        sf::Vector2f _size;

        sf::Text _title;

    };

}

#endif /* MYSF_ALIST_HPP_ */
