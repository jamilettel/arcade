/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include "Core.hpp"
#include "CoreError.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);

    try {
        arc::Core core(av[1]);

        core.run();
    } catch (arc::ArcadeError &error) {
        std::cerr << error.getComponent() << ": " << error.what() << std::endl;
        return (84);
    }

    return (0);
}
