/*
** EPITECH PROJECT, 2020
** Animal
** File description:
** Animal
*/

#ifndef ANIMAL_HPP_
#define ANIMAL_HPP_

class Animal {
public:
    Animal() = default;
    virtual ~Animal() = default;

    virtual void print() = 0;
};

#endif /* ANIMAL_HPP_ */
