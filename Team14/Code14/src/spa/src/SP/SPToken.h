#pragma once

#include <string>
#include "SPTokenType.h"

class SPToken {

private:
    TokenType type;
    std::string value;

public:
    SPToken(TokenType type, const std::string& value);
    SPToken();
    TokenType getType();
    std::string getValue();
};