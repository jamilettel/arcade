/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#ifndef MYSF_LIST_HPP_
#define MYSF_LIST_HPP_

#include <SFML/Graphics.hpp>
#include <functional>
#include "Button/RectButton.hpp"

namespace MySf {

    class List {
    public:

        static Button::ButtonColor defaultAltColors;
        static Button::ButtonColor defaultColors;
        static sf::Color defaultFrameColor;
        static sf::Color defaultTextColor;

        List(sf::RenderWindow &window,
             const std::vector<std::string> &list,
             const std::function<void (const std::string &)> &fct,
             const std::string &title,
             sf::Font &font,
             int chosen = -1);
        ~List() = default;

        void setColors(const Button::ButtonColor &normal,
                       const Button::ButtonColor &alt,
                       const sf::Color &frame,
                       const sf::Color &text);

        void setList(const std::vector<std::string> &list, int chosen = -1);
        const std::vector<std::string> &getList() const;
        void setFct(const std::function<void (const std::string &)> &fct);
        const std::string getTitle() const;
        void setTitle(const std::string &title);

        const sf::Font &getFont() const;
        sf::Font &getFont();

        void draw();

        void setSize(const sf::Vector2f &size);
        void setPos(const sf::Vector2f &pos);
        const sf::Vector2f &getSize() const;
        const sf::Vector2f &getPos() const;

    private:

        void setDrawableObjects();
        void setChosen();

        sf::RenderWindow &_window;
        sf::Font &_font;
        std::vector<std::string> _list;
        std::vector<std::unique_ptr<Button::RectButton>> _listButtons;
        std::function<void (const std::string &str)> _fct;

        Button::ButtonColor _colors;
        Button::ButtonColor _altColors;
        sf::Color _frameColor;
        sf::Color _textColor;

        int _chosen;

        sf::Vector2f _pos;
        sf::Vector2f _size;

        sf::RectangleShape _frame;
        sf::Text _title;

        sf::RectangleShape _elementBackground;
        sf::Text _elementText;

    };

}

#endif /* MYSF_LIST_HPP) */
