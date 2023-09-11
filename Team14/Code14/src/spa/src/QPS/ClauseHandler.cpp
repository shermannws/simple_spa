#include "ClauseHandler.h"

ClauseHandler::ClauseHandler(std::shared_ptr<PkbReader> pkbReader) : pkbReader(pkbReader) {}

void ClauseHandler::setStrategy(std::shared_ptr<Strategy> strategy) {
    strategy = std::move(strategy);
}

void ClauseHandler::executeQuery(Query& query, Result& result) const {
    if (strategy) {
        result = strategy->evaluateClause(query, pkbReader);
    } else {
        throw std::runtime_error("No strategy set for clause handler");
    }
}