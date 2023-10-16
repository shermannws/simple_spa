#include "SemanticError.h"

SemanticError::SemanticError(const std::string &message)
    : std::runtime_error(message) {}