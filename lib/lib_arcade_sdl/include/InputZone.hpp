/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** InputZone
*/

#ifndef INPUT_ZONE_HPP_
#define INPUT_ZONE_HPP_

#include "Color/SmoothShifting.hpp"
#include "MySDL/Window.hpp"
#include "MySDL/Text.hpp"
#include "MySDL/Rectangle.hpp"
#include <memory>
#include <string>

namespace MySDL {

    class InputZone {
    public:
        InputZone(Window &window,
                  const Vector &pos,
                  const Vector &size,
                  Font &font,
                  const std::string &placeHolder);
        ~InputZone() = default;

        void draw();
        void update(const SDL_Event &event);

        void setPosition(Vector pos);
        const Vector &getPosition() const;
        void setSize(Vector pos);
        const Vector &getSize() const;

        void setPlaceHolder(const std::string &placeHolder);
        const std::string &getPlaceHolder() const;

        const Font &getFont() const;

        const std::string &getInput() const;

        void setTextColor(const SDL_Color &color);
        void setBackgroundColor(const SDL_Color &color);
        void setPlaceHolderColor(const SDL_Color &color);
        void setOutlineColor(const SDL_Color &focused, const SDL_Color &unfocused);

        const std::string &getAnsiInput();
        void setInput(const std::string &input);

    private:
        void addChar(Uint32 c);
        void removeChar();

        void applySizeAndPos();

        std::string _placeHolder;
        Font &_font;
        std::string _content;

        size_t _cursorPos;
        Rectangle _cursor;

        bool _hasFocus;
        Window &_window;

        Vector _pos;
        Vector _size;

        Color::SmoothShifting _colorText;
        Color::SmoothShifting _colorBackground;
        Color::SmoothShifting _colorOutline;
        Color::SmoothShifting _colorPlaceHolder;

        SDL_Color _currentOutlineColor;
        SDL_Color _focusOutline;
        SDL_Color _unfocusedOutline;

        Rectangle _rs;
        Text _text;

        bool _isFull;

        bool _mouseButtonPressed;

        Uint32 _currentTicks;
    };

}

#endif /* INPUT_ZONE_HPP_ */
