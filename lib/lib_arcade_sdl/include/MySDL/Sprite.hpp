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
        Sprite();

        Sprite(const std::string &filepath, Window &window);
        ~Sprite();

        Sprite(const Sprite &rhs) = delete;
        Sprite &operator=(const Sprite &rhs) = delete;

        SDL_Texture *getTexture();

        void setPosition(const Vector &pos);
        void setSize(const Vector &size);
        void setRect(const SDL_FRect &rect);

        const Vector &getPosition() const;
        const Vector &getSize() const;
        const SDL_FRect &getRect() const;

        void setRotation(double rotation);
        double getRotation() const;

        void loadFile(const std::string &filepath, Window &window);

        void setColor(const SDL_Color &color);
        const SDL_Color &getColor() const;

    private:
        SDL_Texture *_texture;

        Vector _pos;
        Vector _size;
        SDL_FRect _rect;

        double _rotation;

        SDL_Color _color; // color is used when texture is nullptr
    };

}

#endif /* SDL_SPRITE_HPP_ */
