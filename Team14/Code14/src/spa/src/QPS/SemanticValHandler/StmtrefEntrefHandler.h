#pragma once

#include <stdexcept>

#include "SemanticValHandler.h"

class StmtrefEntrefHandler : public SemanticValHandler {
public:
    void handle(Query &query, std::shared_ptr<Clause> clause) override;
};