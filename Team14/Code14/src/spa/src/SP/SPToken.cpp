#include "SPToken.h"

SPToken::SPToken(TokenType type, std::string value) : type(type), value(std::move(value)) {}
SPToken::SPToken() = default;

TokenType SPToken::getType() { return type; }

std::string SPToken::getValue() { return value; };