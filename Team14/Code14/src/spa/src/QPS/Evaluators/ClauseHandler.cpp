#include <stdexcept>

#include "ClauseHandler.h"

ClauseHandler::ClauseHandler(std::shared_ptr<PkbReader> pkbReader)
    : pkbReader(pkbReader) {}

void ClauseHandler::setStrategy(std::shared_ptr<Strategy> strategy) {
    this->strategy = std::move(strategy);
}

std::shared_ptr<Result>
ClauseHandler::executeClause(std::shared_ptr<Clause> clause) const {
    if (strategy) {
        std::shared_ptr<Result> result = strategy->evaluateClause(clause);
        result->setType(clause->getSynonyms());
        return result;
    } else {
        throw std::runtime_error("No strategy set for clause handler");
    }
}
