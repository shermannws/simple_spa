#pragma once

#include <exception>
#include <iostream>
#include <string>

/**
 * SyntaxException class that extends from std::exception
 */
class SyntaxException : public std::exception {
private:
    /**
     * @brief The error message of the SyntaxException
     */
    std::string errorMsg;

public:
    /**
     * @brief The constructor of SyntaxException
     * @param msg The error message of the exception
     */
    explicit SyntaxException(std::string msg);

    /**
     * @brief Returns the error message of the exception when the exception is thrown
     */
    virtual const char *what() const throw();
};
