/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** main
*/

// #include <caca.h>
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
    }

    return (0);
}

// struct __attribute__((packed)) bmp_header_t
// {
//     uint16_t magic;
//     uint32_t size;
//     uint16_t _app1;
//     uint16_t _app2;
//     uint32_t offset;
// };

// class BitmapReader {
// public:
//     BitmapReader(const std::string &filepath) {
//         std::ifstream ifs(filepath, std::ios::binary);
//         char *buff = nullptr;

//         if (!ifs)
//             throw 0;
//         ifs.seekg(0, std::ios::end);
//         _length = ifs.tellg();
//         buff = new char [_length + 1];
//         buff[_length] = 0;
//         ifs.seekg(0, std::ios::beg);
//         ifs.read(buff, _length);
//         std::cout << _length << std::endl;
//         _buff = static_cast<void *>(buff);
//     }
//     ~BitmapReader() {
//         delete [] static_cast<char *>(_buff);
//     }

//     const void *getContents() const {
//         return (_buff);
//     }

//     const void *getPixelArray() const {
//         bmp_header_t *gmp = static_cast<bmp_header_t *>(_buff);
//         std::cout << gmp->offset << std::endl;

//         return (static_cast<char *>(_buff) + gmp->offset);
//     }

// private:
//     void *_buff;
//     int _length;
// };
