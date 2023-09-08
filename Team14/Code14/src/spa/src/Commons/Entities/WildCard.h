#include "Variable.h"

class WildCard : public Variable {
public:
    WildCard();

    bool isWildCard() override;
};