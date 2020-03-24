/*
** EPITECH PROJECT, 2020
** MySf
** File description:
** AList
*/

#ifndef MYSF_ALIST_HPP_
#define MYSF_ALIST_HPP_

#include "List/IList.hpp"

namespace MySDL {

    class AList: public IList {
    public:
        AList(MySDL::Window &window, MySDL::Font &font,
              const std::vector<std::string> &list,
              const std::string &title);

        virtual void setList(const std::vector<std::string> &list) override;
        virtual const std::vector<std::string> &getList() const override;
        virtual const std::string getTitle() const override;
        virtual void setTitle(const std::string &title) override;

        virtual const MySDL::Font &getFont() const override;
        virtual MySDL::Font &getFont() override;

        virtual void setSize(const MySDL::Vector &size) override;
        virtual void setPos(const MySDL::Vector &pos) override;
        virtual const MySDL::Vector &getSize() const override;
        virtual const MySDL::Vector &getPos() const override;

    protected:
        MySDL::Window &_window;
        MySDL::Font &_font;
        std::vector<std::string> _list;

        MySDL::Vector _pos;
        MySDL::Vector _size;

        MySDL::Text _title;

    };

}

#endif /* MYSF_ALIST_HPP_ */
