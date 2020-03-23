/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Text class wrapper
*/

#ifndef MYSDL_TEXT_HPP_
#define MYSDL_TEXT_HPP_

#include "MySDL/Font.hpp"
#include "MySDL/Window.hpp"

namespace MySDL {

    class Text {
    public:
        Text(Font &font, const std::string &text, int ptsize, Window &window);
        ~Text();

        SDL_Texture *getTexture();

        void setPosition(const Vector &pos);
        void setCharacterSize(int size);
        void setColor(const SDL_Color &color);

        const Vector &getPosition() const;
        const Vector &getSize() const;
        const SDL_Rect &getRect() const;

        const SDL_Color &getColor() const;

    private:
        void loadTexture();

        Window &_window;
        Font &_font;

        SDL_Texture *_texture;

        Vector _pos;
        Vector _size;
        SDL_Rect _rect;

        int _characterSize;
        SDL_Color _color;

        std::string _text;

        bool _loadTexture;
    };

}

#endif /* MYSDL_TEXT_HPP_ */
