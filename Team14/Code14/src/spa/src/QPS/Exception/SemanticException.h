#pragma once

#include <iostream>

class SemanticException : public std::exception {
private:
    std::string errorMsg;
public:
    explicit SemanticException(std::string msg);
    virtual const char* what() const throw();
};

