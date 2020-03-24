/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** List
*/

#ifndef MYSF_LIST_HPP_
#define MYSF_LIST_HPP_

#include "List/BasicList.hpp"
#include "Button/RectButton.hpp"

namespace MySDL {

    class ButtonList: public BasicList {
    public:

        static Button::ButtonColor defaultAltColors;
        static Button::ButtonColor defaultColors;

        ButtonList(Window &window,
                   const std::vector<std::string> &list,
                   const std::function<void (const std::string &)> &fct,
                   const std::string &title,
                   Font &font,
                   int nbDisplayed = 10,
                   int chosen = -1);
        ~ButtonList() = default;

        void setColors(const Button::ButtonColor &normal,
                       const Button::ButtonColor &alt);

        void setFct(const std::function<void (const std::string &)> &fct);

        void setList(const std::vector<std::string> &list) override;
        void setList(const std::vector<std::string> &list, int chosen);

        void drawElement(size_t element, const Vector &pos) override;

        void update(const SDL_Event &event) override;

    private:

        void setChosen();

        std::vector<std::unique_ptr<Button::RectButton>> _listButtons;
        std::function<void (const std::string &str)> _fct;

        Button::ButtonColor _colors;
        Button::ButtonColor _altColors;

        int _chosen;

    };

}

#endif /* MYSF_LIST_HPP) */
