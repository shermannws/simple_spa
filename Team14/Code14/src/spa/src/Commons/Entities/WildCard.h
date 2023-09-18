#pragma once

#include "Variable.h"

class WildCard : public Variable {
public:
    /*!
     * Constructor for Wildcard Variable object
     */
    WildCard();

    /*!
     * Returns true as Wildcard object is a Wildcard
     */
    bool isWildCard() override;
};