/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2019_ISCENE_HPP
#define OOP_ARCADE_2019_ISCENE_HPP

namespace arc {

    class IScene {
    public:
        virtual ~IScene() = default;

        virtual void update() = 0;
        virtual void display() = 0;
        virtual void refresh() = 0;
    };
}
#endif //OOP_ARCADE_2019_ISCENE_HPP
