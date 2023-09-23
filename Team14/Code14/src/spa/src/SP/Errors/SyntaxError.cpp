#include "SyntaxError.h"

SyntaxError::SyntaxError(const std::string &message) : std::runtime_error(message) {}