/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** BasicList header file
*/

#ifndef MYSF_BASICLIST_HPP_
#define MYSF_BASICLIST_HPP_

#include "List/AList.hpp"
#include "Button/RectButton.hpp"
#include "SDLError.hpp"

namespace MySDL {

    class BasicList: public AList {
    public:

        static SDL_Color defaultFrameColor;
        static SDL_Color defaultTextColor;
        static SDL_Color defaultColor;
        static SDL_Color defaultAltColor;

        static Button::ButtonColor defaultButtonColor;
        static Button::ButtonColor defaultTextButtonColor;

        BasicList(MySDL::Window &window,
                  const std::vector<std::string> &list,
                  const std::string &title,
                  MySDL::Font &font,
                  int nbDisplayed = 10);

        virtual void draw() override;

        virtual void setPos(const MySDL::Vector &pos) override;

        // only width is taken into consideration
        virtual void setSize(const MySDL::Vector &size) override;

        virtual void setList(const std::vector<std::string> &list) override;

        virtual int getNbDisplayed() const;
        virtual void setNbDisplayed(int nbDisplayed);

        virtual void setColor(const SDL_Color &frame, const SDL_Color &text,
                      const SDL_Color &color, const SDL_Color &altColor);
        virtual void setColor(const Button::ButtonColor &button,
                      const Button::ButtonColor &text);

        virtual void scroll(int to);
        virtual void update(const SDL_Event &event);
        virtual void drawElement(size_t element, const MySDL::Vector &pos) override;

        size_t getColsNumber() const;

        BasicList &getColumn(size_t nb);

        template <typename Type, typename ...T>
        void addColumn(T &&...vars) {
            if (_next.has_value()) {
                (*_next)->addColumn<Type>(vars...);
            } else {
                MySDL::Vector pos = _pos;

                _next.emplace(std::unique_ptr<BasicList>(new Type(vars...)));
                (*_next)->_prev.emplace(this);
                pos.x += _size.x;
                (*_next)->setPos(pos);
                (*_next)->setSize(_size);
                (*_next)->setNbDisplayed(_nbDisplayed);
            }
        }

        void setListPosition(int pos);

        float getWidth() const;

    protected:
        static const float _buttonHeight;
        MySDL::Vector _elementSize;

        int _nbDisplayed;
        int _position;

    private:

        void setDrawableObjects();

        MySDL::Rectangle _frame;

        MySDL::Rectangle _elementBackground;
        MySDL::Text _elementText;

        SDL_Color _frameColor;
        SDL_Color _textColor;
        SDL_Color _normalColor;
        SDL_Color _altColor;

        Button::ButtonColor _buttonColor;
        Button::ButtonColor _buttonTextColor;

        Button::RectButton _buttonUp;
        Button::RectButton _buttonDown;

        // MySDL::Mouse _mouse;

        std::optional<BasicList *> _prev;
        std::optional<std::unique_ptr<BasicList>> _next;

    };

}

#endif /* MYSF_BASICLIST_HPP_ */
