
#include "SyntaxException.h"

#include <utility>

SyntaxException::SyntaxException(std::string msg) : errorMsg(std::move(msg)) {}

const char *SyntaxException::what() const throw() { return errorMsg.c_str(); }