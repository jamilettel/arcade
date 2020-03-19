/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** BasicList header file
*/

#ifndef MYSF_BASICLIST_HPP_
#define MYSF_BASICLIST_HPP_

#include "MySf/List/AList.hpp"
#include "MySf/Button/RectButton.hpp"
#include "MySf/Error.hpp"

namespace MySf {

    class BasicList: public AList {
    public:

        static sf::Color defaultFrameColor;
        static sf::Color defaultTextColor;
        static sf::Color defaultColor;
        static sf::Color defaultAltColor;

        static MySf::Button::ButtonColor defaultButtonColor;
        static MySf::Button::ButtonColor defaultTextButtonColor;

        BasicList(sf::RenderWindow &window,
                  const std::vector<std::string> &list,
                  const std::string &title,
                  sf::Font &font,
                  int nbDisplayed = 10);

        virtual void draw() override;

        virtual void setPos(const sf::Vector2f &pos) override;

        // only width is taken into consideration
        virtual void setSize(const sf::Vector2f &size) override;

        virtual void setList(const std::vector<std::string> &list) override;

        virtual int getNbDisplayed() const;
        virtual void setNbDisplayed(int nbDisplayed);

        virtual void setColor(const sf::Color &frame, const sf::Color &text,
                      const sf::Color &color, const sf::Color &altColor);
        virtual void setColor(const MySf::Button::ButtonColor &button,
                      const MySf::Button::ButtonColor &text);

        virtual void scroll(int to);
        virtual void update(const sf::Event &event);
        virtual void drawElement(size_t element, const sf::Vector2f &pos) override;

        size_t getColsNumber() const;

        BasicList &getColumn(size_t nb);

        template <typename Type, typename ...T>
        void addColumn(T &&...vars) {
            if (_next.has_value()) {
                (*_next)->addColumn<Type>(vars...);
            } else {
                sf::Vector2f pos = _pos;

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
        sf::Vector2f _elementSize;

    private:

        void setDrawableObjects();

        int _nbDisplayed;
        int _position;

        sf::RectangleShape _frame;

        sf::RectangleShape _elementBackground;
        sf::Text _elementText;

        sf::Color _frameColor;
        sf::Color _textColor;
        sf::Color _normalColor;
        sf::Color _altColor;

        MySf::Button::ButtonColor _buttonColor;
        MySf::Button::ButtonColor _buttonTextColor;

        MySf::Button::RectButton _buttonUp;
        MySf::Button::RectButton _buttonDown;

        sf::Mouse _mouse;

        std::optional<BasicList *> _prev;
        std::optional<std::unique_ptr<BasicList>> _next;

    };

}

#endif /* MYSF_BASICLIST_HPP_ */
