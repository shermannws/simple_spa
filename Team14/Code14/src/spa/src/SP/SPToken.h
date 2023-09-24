#pragma once

#include <string>
#include <utility>

#include "SPTokenType.h"

/**
 * SPTokens which are created by the SPTokenizer when it tokenizes the SIMPLE input source program.
 */
class SPToken {
private:
    /**
     * The type of the SPToken.
     */
    TokenType type;

    /**
     * The value of the SPToken stored as a string.
     */
    std::string value;

public:
    /**
     * Creates and initialises an SPToken.
     * @param type Type of the token
     * @param value Value of the token as a string
     */
    SPToken(TokenType type, std::string  value);

    /**
     * Creates and initialises an empty SPToken.
     */
    SPToken();

    /**
     * Returns the type of the SPToken.
     * @return
     */
    TokenType getType();

    /**
     * Returns the value of the SPToken.
     * @return Value as string
     */
    std::string getValue();
};