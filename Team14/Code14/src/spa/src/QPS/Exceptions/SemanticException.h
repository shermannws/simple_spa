#pragma once

#include <iostream>

/**
 * SemanticException class that extends from std::exception
 */
class SemanticException : public std::exception {
private:
    /**
     * @brief The error message of the SemanticException
     */
    std::string errorMsg;

public:
    /**
     * @brief The constructor of SemanticException
     * @param msg The error message of the exception
     */
    explicit SemanticException(std::string msg);

    /**
     * @brief Returns the error message of the exception when the exception is
     * thrown
     */
    virtual const char *what() const throw();
};
