#pragma once

#include "SemanticValHandler.h"

SemanticValHandler::SemanticValHandler() : nextHandler(nullptr) {}

std::shared_ptr<SemanticValHandler> SemanticValHandler::setNext(std::shared_ptr<SemanticValHandler> handler) {
    nextHandler = handler;
    return nextHandler;
}

void SemanticValHandler::handle(Query &query, std::shared_ptr<Clause> clause) {
    if (nextHandler) {
        return nextHandler->handle(query, clause);
    }
}