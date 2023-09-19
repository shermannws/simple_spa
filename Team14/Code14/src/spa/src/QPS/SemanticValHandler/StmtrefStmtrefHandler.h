#pragma once

#include "SemanticValHandler.h"

class StmtrefStmtrefHandler : public SemanticValHandler {
public:
    void handle(Query &query, std::shared_ptr<Clause> clause) override;
};
