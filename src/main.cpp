/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** main
*/

#include <caca.h>
#include <fstream>
#include <iostream>
#include "IGraphical.hpp"

struct __attribute__((packed)) bmp_header_t
{
    uint16_t magic;
    uint32_t size;
    uint16_t _app1;
    uint16_t _app2;
    uint32_t offset;
};

class BitmapReader {
public:
    BitmapReader(const std::string &filepath) {
        std::ifstream ifs(filepath, std::ios::binary);
        char *buff = nullptr;

        if (!ifs)
            throw 0;
        ifs.seekg(0, std::ios::end);
        _length = ifs.tellg();
        buff = new char [_length + 1];
        buff[_length] = 0;
        ifs.seekg(0, std::ios::beg);
        ifs.read(buff, _length);
        std::cout << _length << std::endl;
        _buff = static_cast<void *>(buff);
    }
    ~BitmapReader() {
        delete [] static_cast<char *>(_buff);
    }

    const void *getContents() const {
        return (_buff);
    }

    const void *getPixelArray() const {
        bmp_header_t *gmp = static_cast<bmp_header_t *>(_buff);
        std::cout << gmp->offset << std::endl;

        return (static_cast<char *>(_buff) + gmp->offset);
    }

private:
    void *_buff;
    int _length;
};

int main(void)
{
    caca_canvas_t *cv; caca_display_t *dp; caca_event_t ev;
    caca_dither_t *dither = NULL;
    BitmapReader img("test.bmp");

    dp = caca_create_display(NULL);
    if (!dp)
        return (1);
    cv = caca_get_canvas(dp);
    dither = caca_create_dither(32, 100, 100, 40, 0xff0000, 0xff00, 0xff, 0xff000000);
    caca_dither_bitmap(cv, 0, 0, 40, 20, dither, img.getContents());
    caca_set_display_title(dp, "Hello!");
    caca_set_color_ansi(cv, CACA_BLACK, CACA_WHITE);
    caca_put_str(cv, 0, 0, "This is a message");
    caca_refresh_display(dp);
    caca_get_event(dp, CACA_EVENT_KEY_PRESS, &ev, -1);
    caca_free_display(dp);
    return (0);
}
