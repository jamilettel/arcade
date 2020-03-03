
#include "Animal.hpp"
#include <iostream>

class Koala: public Animal {
public:
    Koala() = default;

    void print() {
        std::cout << "Kreorg" << std::endl;
    }
};

extern "C" Animal *koala_ctor()
{
    return (new Koala);
}
