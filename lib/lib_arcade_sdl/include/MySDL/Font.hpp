/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Font class wrapper
*/

#ifndef MYSDL_FONT_HPP_
#define MYSDL_FONT_HPP_

#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

namespace MySDL {

    class Font {
    public:
        Font(const std::string &filepath, int ptsize = 32);
        ~Font();

        Font(const Font &rhs) = delete;
        Font &operator=(const Font &rhs) = delete;

        TTF_Font *getFont(int ptsize);
        SDL_Surface *renderText(const std::string &string, int ptsize,
                                const SDL_Color &color = {255, 255, 255, 255});

        void setStyle(int fontStyle);
        int getStyle();

    private:
        void loadFont(int ptsize);

        std::map<int, TTF_Font *> _fonts; // font size cannot be changed after creation
        int _style;

        const std::string _filepath;

    };

}

#endif /* MYSDL_FONT_HPP_ */
