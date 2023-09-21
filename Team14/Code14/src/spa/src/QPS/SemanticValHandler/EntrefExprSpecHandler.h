#pragma once

#include "SemanticValHandler.h"

class EntrefExprSpecHandler : public SemanticValHandler {
public:
    void handle(Query &query, std::shared_ptr<Clause> clause) override;
};
