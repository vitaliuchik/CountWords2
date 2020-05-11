//
// Created by Admin on 22.04.2020.
//

#ifndef COUNTWORDS_EXCEPTIONS_H
#define COUNTWORDS_EXCEPTIONS_H

#include <exception>

class InvalidConfigurationException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Invalid configuration file.";
    }
};

#endif //COUNTWORDS_EXCEPTIONS_H
