/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SDL Sprite class wrapper
*/

#ifndef SDL_SPRITE_HPP_
#define SDL_SPRITE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Window.hpp"

namespace MySDL {

    class Sprite {
    public:
        Sprite(const std::string &filepath, Window &window);
        ~Sprite();

        Sprite(const Sprite &rhs) = delete;
        Sprite &operator=(const Sprite &rhs) = delete;

        SDL_Texture *getTexture();

        void setPosition(const Vector &pos);
        void setSize(const Vector &size);
        void setRect(const SDL_Rect &rect);

        const Vector &getPosition() const;
        const Vector &getSize() const;
        const SDL_Rect &getRect() const;

    protected:
    private:
        SDL_Texture *_texture;

        Vector _pos;
        Vector _size;
        SDL_Rect _rect;
    };

}

#endif /* SDL_SPRITE_HPP_ */
