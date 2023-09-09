#include "SPToken.h"

#include <string>

SPToken::SPToken(TokenType type, const std::string& value): type(type), value(value) {}

TokenType SPToken::getType() {
    return type;
}

std::string SPToken::getValue() {
    return value;
};