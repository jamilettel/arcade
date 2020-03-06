/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** test DLLoader
*/

#include <criterion/criterion.h>
#include "DLLoader.hpp"
#include "Animal.hpp"
#include "Error.hpp"
#include "OSRedirector.hpp"

Test(DLLoader, basic_test)
{
    OSRedirector redirector(std::cout);

    try {
        DLLoader<Animal> koalalib("tests/libkoala.so");
        Animal *koala = koalalib.getInstance("koala_ctor");

        koala->print();
        delete koala;
    } catch (DLLoaderError &e) {
        std::cerr << e.getComponent() << ": "  << e.what()<< std::endl;
        std::cerr << dlerror() << std::endl;
        cr_assert(false);
    }
    cr_assert(redirector.getContent() == "Kreorg\n");
}

Test(DLLoader, invalid_lib)
{
    try {
        DLLoader<Animal *()> koalalib("graphics qui n'existe pas");

        cr_assert(false);
    } catch (ArcadeError &e) {
        cr_assert(e.getComponent() == "DLLoader");
    }
}
