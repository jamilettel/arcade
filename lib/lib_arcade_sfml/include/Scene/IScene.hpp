/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include <SFML/Graphics.hpp>

namespace arc {

    class IScene {
    public:

        virtual ~IScene() = default;

        virtual void draw() = 0;
        virtual void update(const sf::Event &event) = 0;

    };

};

#endif /* ISCENE_HPP_ */
