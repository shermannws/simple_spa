#pragma once

#include <string>
#include <utility>

#include "SPTokenType.h"

class SPToken {

private:
    TokenType type;
    std::string value;

public:
    SPToken(TokenType type, std::string  value);
    SPToken();
    TokenType getType();
    std::string getValue();
};