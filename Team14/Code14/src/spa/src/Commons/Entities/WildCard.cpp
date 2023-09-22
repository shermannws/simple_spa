#include "WildCard.h"

WildCard::WildCard() : Variable("_") {}

bool WildCard::isWildCard() {
    return true;
}