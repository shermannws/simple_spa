#pragma once

#include <stdexcept>

class SemanticError : public std::runtime_error {
public:
    explicit SemanticError(const std::string& message);
};