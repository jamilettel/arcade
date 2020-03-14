/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** InputZone
*/

#ifndef INPUT_ZONE_HPP_
#define INPUT_ZONE_HPP_

#include "Color/SmoothShifting.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace MySf {

    class InputZone {
    public:
        InputZone(sf::RenderWindow &window,
                  const sf::Vector2f &pos,
                  const sf::Vector2f &size,
                  sf::Font &font,
                  const std::string &placeHolder);
        ~InputZone() = default;

        void draw();
        void update(const sf::Event &event);

        void setPosition(sf::Vector2f pos);
        const sf::Vector2f &getPosition() const;
        void setSize(sf::Vector2f pos);
        const sf::Vector2f &getSize() const;

        void setPlaceHolder(const std::string &placeHolder);
        const sf::String &getPlaceHolder() const;

        void setFont(const sf::Font &font);
        const sf::Font &getFont() const;

        const sf::String &getInput() const;

        void setTextColor(const sf::Color &color);
        void setBackgroundColor(const sf::Color &color);
        void setPlaceHolderColor(const sf::Color &color);
        void setOutlineColor(const sf::Color &focused, const sf::Color &unfocused);

        const std::string &getAnsiInput();

    private:
        void addChar(sf::Uint32 c);
        void removeChar();

        void applySizeAndPos();

        sf::String _placeHolder;
        sf::Font &_font;
        sf::String _content;
        std::string _stringContent;

        size_t _cursorPos;
        sf::RectangleShape _cursor;

        bool _hasFocus;
        sf::Mouse _mouse;
        sf::RenderWindow &_window;

        sf::Vector2f _pos;
        sf::Vector2f _size;

        Color::SmoothShifting _colorText;
        Color::SmoothShifting _colorBackground;
        Color::SmoothShifting _colorOutline;
        Color::SmoothShifting _colorPlaceHolder;

        sf::Color _currentOutlineColor;
        sf::Color _focusOutline;
        sf::Color _unfocusedOutline;

        sf::RectangleShape _rs;
        sf::Text _text;

        sf::Clock _clock;

        bool _isFull;
    };

}

#endif /* INPUT_ZONE_HPP_ */
