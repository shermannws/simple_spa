#pragma once

#include <memory>
#include "QPS/Query.h"

class SemanticValHandler {
private:
    std::shared_ptr<SemanticValHandler> nextHandler;
public:
    explicit SemanticValHandler();
    virtual ~SemanticValHandler() = default;
    std::shared_ptr<SemanticValHandler> setNext(std::shared_ptr<SemanticValHandler> handler);
    virtual void handle(Query& query, std::shared_ptr<Clause> clause) = 0;
};