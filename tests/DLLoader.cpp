/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** test DLLoader
*/

#include <criterion/criterion.h>
#include "DLLoader.hpp"
#include "Koala.hpp"
#include "Error.hpp"
#include "OSRedirector.hpp"

Test(DLLoader, basic_test)
{
    OSRedirector redirector(std::cout);

    try {
        DLLoader<Koala> koalalib("tests/libkoala.so");
        Koala *koala = koalalib.getInstance("koala_ctor");

        koala->print();
        delete koala;
    } catch (DLLoaderError &e) {
        cr_assert(false);
    }
    cr_assert(redirector.getContent() == "GRAHU\n");
}

Test(DLLoader, invalid_lib)
{
    try {
        DLLoader<Koala *()> koalalib("lib qui n'existe pas");

        cr_assert(false);
    } catch (ArcadeError &e) {
        cr_assert(e.getComponent() == "DLLoader");
    }
}
