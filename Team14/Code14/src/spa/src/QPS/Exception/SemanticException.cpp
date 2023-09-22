
#include "SemanticException.h"

#include <utility>

SemanticException::SemanticException(std::string msg) : errorMsg(std::move(msg)) {}

const char* SemanticException::what() const throw() {
    return errorMsg.c_str();
}