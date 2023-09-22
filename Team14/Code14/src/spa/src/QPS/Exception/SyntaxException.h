#pragma once

#include <string>
#include <exception>
#include <iostream>

class SyntaxException : public std::exception {
private:
    std::string errorMsg;
public:
    explicit SyntaxException(std::string msg);
    virtual const char* what() const throw();
};

