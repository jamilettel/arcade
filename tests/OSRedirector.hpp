/*
** EPITECH PROJECT, 2020
** tests
** File description:
** os redirector
*/

#ifndef OSREDIRECTOR_HPP_
#define OSREDIRECTOR_HPP_

#include <ostream>
#include <iostream>
#include <criterion/criterion.h>

class OSRedirector {
private:
    std::ostringstream _oss;
    std::streambuf *_backup;
    std::ostream &_c;


public:
    OSRedirector(std::ostream &c);

    ~OSRedirector();

    const std::string getContent();
};

#endif /* OSREDIRECTOR_HPP_ */
