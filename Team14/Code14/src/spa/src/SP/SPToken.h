#ifndef SPA_SPTOKEN_H
#define SPA_SPTOKEN_H

#include <string>
#include "SPTokenType.h"

class SPToken {

private:
    TokenType type;
    std::string value;

public:
    SPToken(TokenType type, const std::string& value);
    TokenType getType();
    std::string getValue();
};

#endif //SPA_SPTOKEN_H
